#include <fstream>
#include <vector>
using namespace std;

bool Branje_Stevil(vector<int> &vec, const char s[]) {
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

void Izpis_Stevil(int* polje, unsigned int velikost) {
	ofstream output("out.txt");

	for (int i = 0; i<velikost; i++)
		output << polje[i] << ' ';
}

int main(int argc, const char* argv[]) {
	vector<int> A;

	if (argc < 3) return 0;
	if (!Branje_Stevil(A, argv[2])) return 0;

	if (argv[1][0] == '0') {

		//negativne vrednosti
		int min = A[0];
		for (int i = 0; i < A.size(); i++)
		{
			if (A[i] < min) min = A[i];			//poiscemo min vrednost
		}
		for (int i = 0; i < A.size(); i++)
		{
			A[i] -= min;						//odstejemo min vrednost
		}
		//-------------------------------------

		//1.korak
		int max = A[0];
		for (int i = 0; i < A.size(); i++)
		{
			if (A[i] > max) max = A[i];			//poiscemo max vrednost
		}
		vector<int>C;
		for (int i = 0; i < max + 1; i++)
		{
			C.push_back(0);						//inicializiramo vse vrednosti v C na 0
		}
		//-------------------------------------

		//2.korak
		for (int i = 0; i < A.size(); i++)
		{
			C[A[i]]++;							//sestejemo vrednosti polja C
		}
		//-------------------------------------

		//3.korak
		for (int i = 1; i < C.size(); i++)
		{
			C[i] = C[i] + C[i - 1];
		}
		//-------------------------------------

		//4.korak								//od zadnjega naprej (stabilnost - ohranimo vrstni red stevil)
		vector<int>B(A.size());
		for (int i = A.size() - 1; i >= 0; i--)
		{
			B[C[A[i]] - 1] = A[i];

			C[A[i]]--;
		}
		//-------------------------------------

		//pretvorba nazaj
		for (int i = 0; i < B.size(); i++)
		{
			B[i] += min;
		}
		//-------------------------------------
		
		for (int i = 0; i < A.size(); i++)
		{
			A[i] = B[i];
		}
		Izpis_Stevil(&A[0], A.size());
	}
	else {
		//negativne vrednosti
		int min = A[0];
		for (int i = 0; i < A.size(); i++)
		{
			if (A[i] < min) min = A[i];			//poiscemo min vrednost
		}
		for (int i = 0; i < A.size(); i++)
		{
			A[i] -= min;						//odstejemo min vrednost
		}
		//-------------------------------------

		//1.korak
		int max = A[0];
		for (int i = 0; i < A.size(); i++)
		{
			if (A[i] > max) max = A[i];			//poiscemo max vrednost
		}
		vector<int>C;
		for (int i = 0; i < max + 1; i++)
		{
			C.push_back(0);						//inicializiramo vse vrednosti v C na 0
		}
		//-------------------------------------

		//2.korak
		for (int i = 0; i < A.size(); i++)
		{
			C[A[i]]++;							//sestejemo vrednosti polja C
		}
		//-------------------------------------

		//3.korak
		vector<int>B(A.size());
		int k = 0;
		for (int i = 0; i < C.size(); i++)
		{
			if (C[i] != 0)
			{
				for (int j = 0; j < C[i]; j++)
				{
					B[k] = i;
					k++;
				}
			}
		}
		//-------------------------------------

		//pretvorba nazaj
		for (int i = 0; i < B.size(); i++)
		{
			B[i] += min;
		}
		//-------------------------------------

		for (int i = 0; i < A.size(); i++)
		{
			A[i] = B[i];
		}
		Izpis_Stevil(&A[0], A.size());
	}

	return 0;
}
