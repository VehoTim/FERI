#include <iostream>

using namespace std;

//Prototip funkcije
bool prastevilo(int);
int koliko();
double avgPrastevil(int[20], int);


//Funkcije

//Izracun prastevila
bool prastevilo(int st) {
	int stDel = 0;

	for (int i = 2; i <= sqrt(st); i++)
	{
		if (st % i == 0)
		{
			stDel++;

			if (stDel > 0) break;
		}
	}

	if (st > 1 && stDel == 0) {
		return true;
	}

	else return false;
}

//Izracun koliko prastevil je med -217 in 9001
int koliko() {
	int stPras = 0;

	for (int j = -217; j <= 9001; j++)
	{
		if (prastevilo(j)==true)
		{
			stPras++;
		}
	}

	return stPras;
}

//Povprečna vrednost prvih 20ih prastevil po st
double avgPrastevil(int polje [20], int st) {
	int stPras = 0;

	double skup = 0;

	while (stPras < 20)
	{
		if (prastevilo(st) == true)
		{
			polje[stPras] = st;
			stPras++;

			skup += st;
		}
		st++;
	}

	return skup / 20;
}

int main()
{
	//Izracun prastevila
	int st;
	cout << "Vpisi stevilo: ";
	cin >> st;

	if (prastevilo(st) == true) cout << "Stevilo " << st << " je prastevilo\n";
	else cout << "Stevilo " << st << " ni prastevilo\n";
	//-------------------------------------------------------------------------

	//Izracun stevila prastevil
	cout << "Med -217 in 9001 je " << koliko() << " prastevil.";
	//-------------------------------------------------------------------------

	//Polje se v funkcijo poslje po ref. zato se podatki shranjujejo v to polje
	int polje[20];

	cout << avgPrastevil(polje, 0);
	//-------------------------------------------------------------------------

	//Iskanje najbližjega prastevila v polju, korenu st2 
	int st2;
	cout << "\nVpisi novo stevilo: ";
	cin >> st2;

	double raz;
	double min_raz = 1000000;
	int pos;
	for (int l = 0; l < 20; l++)
	{
		double koren = sqrt(st2);

		if (koren - polje[l] < 0)
		{
			raz = (koren - polje[l]) * -1;
		}
		else raz = koren - polje[l];

		if (raz < min_raz)
		{
			min_raz = raz;
			pos = l;
		}
	}

	cout << polje[pos];
	//--------------------------------------------------------------------------
}
