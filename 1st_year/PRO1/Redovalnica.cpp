#include <iostream>
#include <stdlib.h> 
#include <iomanip>

using namespace std;

void randOcene(int ocene[166][7]) {
	srand(time(NULL));
	//Zaporedna številka
	for (int i = 0; i < 166; i++)
	{
		ocene[i][0] = i + 1;
	}

	for (int i = 0; i < 166; i++)
	{	
		ocene[i][1] = rand() % 30;
		ocene[i][2] = rand() % 20;
	}

	for (int i = 0; i < 166; i++)
	{
		for (int j = 3; j < 6; j++)
		{
			ocene[i][j] = rand() % 101;
		}
	}

	for (int i = 0; i < 166; i++)
	{
		/*RV; VI; RV,VI na koncu*/
		if (ocene[i][4] < 50 && ocene[i][5] < 50) ocene[i][6] = -2;
		else if(ocene[i][5] < 50) ocene[i][6] = -1;
		else if (ocene[i][4] < 50) ocene[i][6] = 0;
		else ocene[i][6] = ((ocene[i][3] * 0.15 + ocene[i][4] * 0.35 + ocene[i][5] * 0.50)/10)+1;
	}
}

int minEl(int ocene[166][7], const int n) {
	int ind = 0;
	for (int i = 1; i < n; i++)
	{
		if (ocene[ind][6] > ocene[i][6]) {
			ind = i;
		}
	}
	return ind;
}

void razporeditev(int ocene[166][7], int vel) {
	for (int i = vel-1; i > 0; i--)
	{
		int ind = minEl(ocene, i);
		if (ocene[ind][6] < ocene[i][6]) {
			swap(ocene[ind], ocene[i]);
		}
	}
}

int main()
{
	int ocene[166][7];

	string imena[30] = { "Tim", "Nejc", "Zan", "Donald", "Jenn", "Will", "Suzan", "Bill", "Bob", "Bard", 
						 "Geralt", "Samantha", "Kassandra", "Demios", "Ales", "Janez","Boris", "Borut", "Bojan", "Tadej", 
						 "Thomas", "Inugami", "Usada", "Gawr", "Mori", "Ina", "Spock", "Rok", "Klemen", "Herman"};

	string priimki[20] = { "Vehovar", "Jones", "Smith", "Rojnik", "Novak", "Prehiter", "Korone", "Gura", "Pekora", "Miller",
						  "Klujn", "Sifko", "Didko", "Eugene", "Young", "Hoppins", "Poppins", "Rodriguez", "Dido", "Belfast" };
	
	randOcene(ocene);

	razporeditev(ocene, 166);

	cout << setw(10) << left << "Zap. st." << setw(21) << left << "Ime in priimek:" << setw(8) << "KV" << setw(8) << "RV" << setw(8) << "VI" << setw(4) << "OC" << endl;
	for (int i = 0; i < 166; i++) {
		string ime = imena[ocene[i][1]] + " " + priimki[ocene[i][2]];
		cout << setw(8) << ocene[i][0] << "| " << setw(19) << left << ime << "| ";

		for (int j = 3; j < 7; j++)
		{
			if (j == 6 && ocene[i][6] == -2) cout << setw(6) << "RV,VI" << "| "; 
			else if (j == 6 && ocene[i][6] == -1) cout << setw(6) << "RV" << "| ";
			else if (j == 6 && ocene[i][6] == 0) cout << setw(6) << "VI" << "| ";
			else cout << setw(6) << ocene[i][j] << "| ";
		}
		cout << endl;
	}

	int skupaj = 0;
	int koliko = 0;

	for (int i = 0; i < 166; i++)
	{

		if (ocene[i][5] >= 50 && ocene[i][6] > 5)
		{
			skupaj = skupaj + ocene[i][6];
			koliko++;
		}
	}

	double povprecje = skupaj / koliko;
	cout << endl << "Povprecna ocena studentov, ki so opravili izpit je " << povprecje;

	int raz;
	int minRaz = 10;
	for (int i = 0; i < 166; i++)
	{	
		if (povprecje - ocene[i][6] < 0)
		{
			raz = (povprecje - ocene[i][6]) * -1;
		}
		else raz = (povprecje - ocene[i][6]);

		if (raz < minRaz) {
			minRaz = raz;
		}
	}

	cout <<  " (najblizje pod zaporedno st.: ";
	for (int i = 0; i < 166; i++)
	{
		if(ocene[i][6] == minRaz+ povprecje || ocene[i][6] == minRaz- povprecje)
			cout << ocene[i][0] << ", ";
	}
	cout << ")";
}
