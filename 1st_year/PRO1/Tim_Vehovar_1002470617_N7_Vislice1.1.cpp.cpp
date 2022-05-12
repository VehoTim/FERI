#include <iostream>
#include <string>
#include <stdlib.h> 
#include <iomanip>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <fstream>

using namespace std;


//Igralec
struct Igralec {
	string ime;
	int vpisnaSt;
	string trenutnoG;
	vector<char> ugibaneCrke;
	int cas;
};

//Enosmerno povezani seznam
struct node {
	Igralec ig;
	node* next = NULL;
};


//Globalne spremenljivke
node* prviIgralec = NULL;
int vstavljenId = 0;
fstream besede;
ifstream myFile;
ofstream newFile;


//Nakljucna izbira gesla
string rndGeslo(int stCrk) {
	srand(time(NULL));
	string line;
	int rnd = rand() % 20;
	switch (stCrk){
	case 5: {
		besede.open("besede5.txt");
		for (int i = 0; i < 20 && getline(besede, line); i++){
			if (i == rnd) {
				return line;
			}
		}
	}
		break;
	case 6: {
		besede.open("besede6.txt");
		for (int i = 0; i < 20 && getline(besede, line); i++) {
			if (i == rnd) {
				return line;
			}
		}
	}
		break;
	case 7: {
		besede.open("besede7.txt");
		for (int i = 0; i < 20 && getline(besede, line); i++) {
			if (i == rnd) {
				return line;
			}
		}
	}
		break;
	case 8: {
		besede.open("besede8.txt");
		for (int i = 0; i < 20 && getline(besede, line); i++) {
			if (i == rnd) {
				return line;
			}
		}
	}
		break;
	case 9: {
		besede.open("besede9.txt");
		for (int i = 0; i < 20 && getline(besede, line); i++) {
			if (i == rnd) {
				return line;
			}
		}
	}
		break;
	default:
		cout << "To se naj nebi zgodilo.";
		break;
	}
}

//Funkcija dodaj
void dodaj(node* igralec) {
	node* tmp = prviIgralec;
	int poz = 1;
	while (tmp != NULL) {
		if (tmp->ig.ugibaneCrke.size() <= igralec->ig.ugibaneCrke.size()) {
			poz++;
		}
		tmp = tmp->next;
	}

	if (poz >= 5) {
		return;
	}

	if (poz == 1) {
		igralec->next = prviIgralec;
		prviIgralec = igralec;
		return;
	}

	tmp = prviIgralec;
	for (int i = 0; i < poz - 2; i++) {
		tmp = tmp->next;
	}
	igralec->next = tmp->next;
	tmp->next = igralec;

	tmp = prviIgralec;
	if (vstavljenId > 5) {
		for (int i = 0; i < 4; i++)
		{
			tmp = tmp->next;
		}
		tmp->next = NULL;
	}
}

//Funkcija izpisi
void izpisi() {
	node* izpis = prviIgralec;
	newFile.open("izpis.txt");
	newFile << "Imena:" << endl;
	while (1)
	{
		newFile << " Ime:" << izpis->ig.ime << ", cas: " << izpis->ig.cas << ", stevilo poskusov: " << izpis->ig.ugibaneCrke.size() << endl;
		if (izpis->next == nullptr)break;
		izpis = izpis->next;
	}
	newFile.close();
}

int main()
{
	char crka;
	bool izrisi;

	while (vstavljenId < 10)
	{
		myFile.open("vislice.txt");
		node* tmp = new node();
		cout << "\nVpisi igralca: ";
		cin >> tmp->ig.ime;
		vstavljenId++;
		tmp->ig.vpisnaSt = vstavljenId;

		//Nastavitev gesla
		cout << "Koliko crk naj ima iskano geslo? (5-9) ";
		int stCrk;
		while (1)
		{
			cin >> stCrk;
			if (stCrk > 4 && stCrk < 10) break;
			else {
				cout << "\nVneseno stevilo crk ni na voljo, poskusi ponovno: ";
			}
		}
		tmp->ig.trenutnoG = rndGeslo(stCrk);
		besede.close();

		//Izpis imena
		cout << "\nZacetek igre za " << tmp->ig.ime << endl;

		int narobe = 0;
		int dolGesla = tmp->ig.trenutnoG.length();

		//Pocaka se na uporabnikov vnos
		system("pause");
		//Zacetek stetje casa
		clock_t start = clock();

		//Logika igre
		for (int j = 0; narobe < 10 && dolGesla > 0; j++)
		{
			char crka;
			cout << tmp->ig.ime << " vpisi crko: ";
			cin >> crka;

			//Preveri se ali je vpisana crka ze bila vpisana in se vstavi v ugibane crke
			if (find(tmp->ig.ugibaneCrke.begin(), tmp->ig.ugibaneCrke.end(), tolower(crka)) == tmp->ig.ugibaneCrke.end()) {
				tmp->ig.ugibaneCrke.emplace_back(tolower(crka));
				int najd = 0;
				//Izpis uganjenih in neuganjenih crk
				for (int k = 0; k < tmp->ig.trenutnoG.length(); k++)
				{
					bool iz = false;
					for (int l = 0; l < tmp->ig.ugibaneCrke.size() - 1; l++)
					{
						if (tmp->ig.ugibaneCrke[l] == tmp->ig.trenutnoG[k]) {
							cout << tmp->ig.trenutnoG[k];
							iz = true;
						}
					}
					if (tmp->ig.trenutnoG[k] == tmp->ig.ugibaneCrke[j]) {
						cout << tmp->ig.trenutnoG[k];
						najd++;
					}
					else if (iz == false) cout << "_";
				}
				cout << endl;
				dolGesla = dolGesla - najd;
				if (najd == 0) {
					narobe++;
					izrisi = true;
				}
				else izrisi = false;

				if (izrisi && myFile.is_open()) {
					string line;
					for (int vrstice = (narobe *10); vrstice < ((narobe * 10) +10); vrstice++)
					{
						getline(myFile, line);
						cout << line << endl;
					}
				}
			}
			else {
				cout << "\nTo crko si ze vpisal, poskuski ponovno.\n";
				j--;
			}
		}

		//Cas se ustavi in vstavi v strukturo
		clock_t end = clock();
		tmp->ig.cas = ((double)(end - start)) / CLOCKS_PER_SEC;


		if (vstavljenId == 1) {
			prviIgralec = tmp;
		}
		else dodaj(tmp);
		myFile.close();
	}

	izpisi();
}