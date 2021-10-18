#include <iostream>
#include <cmath>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;


class BinReader {
public:
	int k;
	ifstream f;
	char x;
	int y;
	float z = 0.0f;

	BinReader(const string path) : k(0) {
		f.open(path, ios::binary);
	}

	bool readBit() {
		if (k == 8) {
			readByte();
			k = 0;
		}
		bool b = (x >> k) & 1;
		k++;
		return b;
	}

	char readByte() {
		f.read((char*)&x, 1);
		return x;
	}

	int readInt() {
		f.read((char*)&y, 4);
		return y;
	}

	float readFloat() {
		f.read((char*)&z, sizeof(z));
		return z;
	}
};

class BinWriter {
public:
	int k;
	ofstream f;
	char x;

	BinWriter(const string path) : k(0) {
		f.open(path, ios::binary);
	}

	~BinWriter() {
		if (k > 0) writeByte(x);
		f.close();
	}

	void writeBit(bool b) {
		if (k == 8) {
			writeByte(x);
			k = 0;
		}
		x ^= (-b ^ x) & (1 << k);
		k++;
	}

	void writeByte(char x) {
		f.write((char*)&x, 1);
	}

	void writeInt(int y) {
		f.write((char*)&y, 4);
	}

	void writeFloat(float z) {
		f.write((char*)&z, 4);
	}
};


void LZWkompresija(string bes, int max, unordered_map<string, int>& S) {
	BinWriter bw("out_c.bin");
	int index = 256;
	int razmerje = 0;
	string T = "";
	int stBitov = ceil(log2(max + 1));
	int cur;
	for (int i = 0; i < bes.length(); i++)
	{
		if (!(S.find(T + bes[i]) == S.end())) T = T + bes[i];
		else {
			cur = S[T];
			for (int j = pow(2, stBitov - 1); j > 0; j /= 2)
			{
				if (cur / j >= 1) {
					//cout << 1;
					bw.writeBit(1);
					cur = cur - j;
				}
				else {
					//cout << 0;
					bw.writeBit(0);
				}
			}
			razmerje++;

			if (index >= max) {
				string znak;
				S.clear();
				for (int i = 0; i < 256; i++)
				{
					znak = (unsigned char)(i);
					S[znak] = (i);
				}
				index = 256;
			}
			S[T + bes[i]] = index;
			index++;
			T = bes[i];
		}
		if (i == bes.length() - 1) {
			cur = S[T];
			for (int j = pow(2, stBitov - 1); j > 0; j /= 2)
			{
				if (cur / j >= 1) {
					//cout << 1;
					bw.writeBit(1);
					cur = cur - j;
				}
				else {
					//cout << 0;
					bw.writeBit(0);
				}
			}
			razmerje++;
		}
	}
	bw.writeByte(bw.x);
	bw.f.close();
	cout << endl << "Kompresijsko razmerje: " << (float)(bes.length() * 8) / (float)(razmerje * stBitov);
}

void LZWdekompresija(string path, int max, unordered_map<string, int>& S) {
	string T = "";

	int index = 256; 
	int curIndex = 0;

	BinReader br(path);
	BinWriter bw("out_d.bin");

	int stBitov = ceil(log2(max + 1));
	int pos;


	string P = "";
	br.readByte();
	while (br.f.peek() != EOF) {
		pos = stBitov - 1;
		curIndex = 0;
		string T = "";
		for (int i = 0; i < stBitov; i++) {
			bool b = br.readBit();

			if (b) curIndex += pow(2, pos);
			pos--;
		}

		string izpis = "";
		if (S.size() > curIndex) {

			for (auto& it : S)
			{	
				if (it.second == curIndex) {
					for (int i = 0; i < it.first.length(); i++)
					{
						izpis = it.first;
					}
				}
			}
		}
		else {
			izpis = P + P[0];
			S[izpis] = index;
			index++;
		}

		for (int i = 0; i < izpis.length(); i++) {
			bw.writeByte(izpis[i]);
		}

		if (!izpis.empty()) {
			if (S.find(P + izpis[0]) == S.end()) {
				S[P + izpis[0]] = index;
				index++;
				if (S.size() >= max) {
					string znak;
					S.clear();
					for (int i = 0; i < 256; i++)
					{
						znak = (unsigned char)(i);
						S[znak] = (i);
					}
					index = 256;
				}
			}
		}
		P = izpis;
	}
}

//
//int main()
//{
//	BinReader br("lorem_ipsum.txt");
//	string bes;
//
//	while (!br.f.eof())
//	{
//		bes += br.readByte();
//	}
//	bes.pop_back();
//	br.f.close();
//	int N = 1024;
//	string znak;
//	unordered_map<string, int> slovar(N);
//	for (int i = 0; i < 256; i++)
//	{
//		znak = (unsigned char)(i);
//		slovar[znak] = (i);
//	}
//	LZWkompresija(bes, N, slovar);
//
//	unordered_map<string, int> slovar2(N);
//	for (int i = 0; i < 256; i++)
//	{
//		znak = (unsigned char)(i);
//		slovar2[znak] = (i);
//	}
//	LZWdekompresija("out_c.bin", N, slovar2);
//}


int main(int argc, const char* argv[])
{
	if (argc < 3) {
		return -1;
	}

	string s = argv[3];
	char c = argv[1][0];
	string N = argv[2];

	string znak;
	unordered_map<string, int> slovar(stoi(N));


	for (int i = 0; i < 256; i++)
	{
		znak = (unsigned char)(i);
		slovar[znak] = (i);
	}

	string bes;
	if (c == 'c') {
		BinReader br(s);
		while (!br.f.eof())
		{
			bes += br.readByte();
		}
		bes.pop_back();
		br.f.close();

		LZWkompresija(bes, stoi(N), slovar);
	}
	else if (c == 'd') {
		LZWdekompresija(s, stoi(N), slovar);
	}
}
