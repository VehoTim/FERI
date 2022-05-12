#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool Branje_Stevil(vector<unsigned char>& vec, const char s[]) {
	ifstream input(s);
	int st;

	if (!input.is_open()) {
		return false;
	}

	while (!input.eof()) {
		input >> st;
		vec.push_back(st);
		while (isspace(input.peek())) input.get();
	}
	input.close();
	return true;
}

void Izpis_Stevil(unsigned char* polje, unsigned int velikost) {
	ofstream output("out.txt");

	for (int i = 0; i < velikost; i++)
		output << (int)polje[i] << ' ';
}

void binSort(vector<unsigned char> &A, int k) {
	vector<unsigned char> B;
	int C[2]{0,0};
	
	for (int i = 0; i < A.size(); i++) B.push_back(0);

	for (int i = 0; i < A.size(); i++) C[(A[i] >> k) & 1]++;

	C[1] += C[0];

	for (int i = A.size() - 1; i >= 0; i--)	B[--C[(A[i] >> k) & 1]] = A[i];

	swap(A, B);

	B.clear();
}

int main(int argc, const char* argv[])
{
	vector<unsigned char> A;

	if (argc < 2) return 0;
	if (!Branje_Stevil(A, argv[1])) return 0;

	for (int k = 0; k < 8; k++) binSort(A, k);

	Izpis_Stevil(&A[0], A.size());
}
