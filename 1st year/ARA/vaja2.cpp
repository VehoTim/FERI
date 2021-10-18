#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

ofstream out;

string inputText(const string &pot) {
	ifstream input(pot);
	stringstream sstream;

	if (!input.is_open()) {
		return string();
	}
	
	sstream << input.rdbuf();
	return sstream.str();
}

void izpis_KMPnext(const int* polje, int len) {
	for (int i = 0; i < len; ++i) {
		out << polje[i] << ' ';
	}
	out << endl;
}

void KMP(const string& text, const string& vzorec) {
	/*
	 * implementacija algoritma KMP 
	 * za izpis polja KMPnext lahko uporabite funkcijo izpis_KMPnext
	 * Za izpis navidezne spremenljivke index uporabite: out << index << ' ';
	 */

	int* kmpNext = new int[vzorec.length()];
	kmpNext[0] = -1;
	kmpNext[1] = 0;

	string tmp1 = "";
	string tmp2 = "";

	for (int i = 2; i < vzorec.length(); i++)
	{
		for (int k = 1; k < i; k++)
		{
			tmp1.clear();
			tmp2.clear();
			for (int j = 0; j < i - k; j++) tmp1.push_back(vzorec[j]);
			for (int j = k; j < i; j++) tmp2.push_back(vzorec[j]);

			if (tmp1 == tmp2) {
				kmpNext[i] = tmp1.length();
				break;
			}
			else kmpNext[i] = 0;
		}
	}

	izpis_KMPnext(kmpNext, vzorec.length());

	vector<int> index;
	int j = 0;

	for (int i = 0; i < vzorec.length(); i++)
	{
		if ((text.length() - vzorec.length()) < j) break;

		if (vzorec[i] != text[j + i]) {
			j = j + i - kmpNext[i];
			i = 0;
		}

		if (i == vzorec.length() - 1) {
			index.push_back(j);
			i = 0;
			j += vzorec.length();
		}
	}

	for (int el : index) {
		out << el << " ";
	}
}

int main(int argc, const char *const argv[]) {
	if (argc != 3) {
		return -1;
	}

	string text = inputText(argv[2]);
	string vzorec = argv[1];
	out.open("out.txt");

	if (!out) {
		return -2;
	}

	KMP(text, vzorec);
	return 0;
}