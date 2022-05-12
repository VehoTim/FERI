#include <iostream>
#include <string>
#include <stdlib.h> 
#include <iomanip>
#include <algorithm>
#include <vector> 
#include <time.h>


using namespace std;

//Struktura za igralca
struct Igralec {
	string ime;
	int vpisnaSt;
	string trenutnoG;
	vector<char> ugibaneCrke;
	int cas;
};

//Nakljucna izbira gesla
string rndGeslo(string gesla[100]) {
	srand(time(NULL));
	return gesla[rand() % 100];
}

//Iskanje najmanjsega stevila ugibanj
int minSt(Igralec igralci[5], const int n) {
	int ind = 0;
	for (int i = 1; i < n; i++)
	{
		if (igralci[ind].ugibaneCrke.size() > igralci[i].ugibaneCrke.size())
		{
			ind = i;
		}
	}
	return ind;
}

int main()
{
	//Scenariji
	const char* scenarij1 =
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";

	const char* scenarij2 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **             \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";


	const char* scenarij3 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";

	const char* scenarij4 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *        |     \n"
		"       *        |     \n"
		"       *              \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";


	const char* scenarij5 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *        |     \n"
		"       *        |     \n"
		"       *       /      \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";


	const char* scenarij6 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *        |     \n"
		"       *        |     \n"
		"       *       / \\   \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";

	const char* scenarij7 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *     --=|     \n"
		"       *        |     \n"
		"       *       / \\   \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";


	const char* scenarij8 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *     --=|=--  \n"
		"       *        |     \n"
		"       *       / \\   \n"
		"       *              \n"
		"      * *             \n"
		"     *   *            \n";


	const char* scenarij9 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *     --=|=--  \n"
		"       *        |     \n"
		"       *       / \\   \n"
		"       *              \n"
		"      * *  GAME       \n"
		"     *   *            \n";

		const char* scenarij10 =
		"       *  * * * *     \n"
		"       * *      *     \n"
		"       **      -O-    \n"
		"       *     --=|=--  \n"
		"       *        |     \n"
		"       *       / \\   \n"
		"       *              \n"
		"      * *  GAME OVER! \n"
		"     *   *            \n";

	const char* scenariji[10] = { scenarij1,scenarij2,scenarij3, scenarij4, scenarij5,scenarij6, scenarij7, scenarij8, scenarij9, scenarij10 };

	//100 gesel
	string gesla[100]{"geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov",
					  "geslo", "ime", "cena", "petelin", "bolha","programiranje", "baza", "demon", "matematika","domov" };

	//Vpis igralcev
	Igralec igralci[5];
	for (int i = 0; i < 5; i++)
	{
		cout << "Vpisi ime " << i+1 << ". igralca: ";
		cin >> igralci[i].ime;
		igralci[i].vpisnaSt = i+1;
	}

	for (int i = 0; i < 5; i++)
	{
		//Izpis imena
		cout << "\nZacetek igre za: " << igralci[i].ime << endl;
		//Nastavitev gesla
		igralci[i].trenutnoG = rndGeslo(gesla);

		int narobe = -1;
		int dolGesla = igralci[i].trenutnoG.length();

		//Pocaka se na uporabnikov vnos
		system("pause");
		//Zacetek stetje casa
		clock_t start = clock();

		//Logika igre
		for (int j = 0; narobe < 9 && dolGesla > 0; j++)
		{
			char crka;
			cout << igralci[i].ime << " vpisi crko: ";
			cin >> crka;

			//Preveri se ali je vpisana crka ze bila vpisana in se vstavi v ugibane crke
			if (find(igralci[i].ugibaneCrke.begin(), igralci[i].ugibaneCrke.end(), tolower(crka)) == igralci[i].ugibaneCrke.end()) {
				igralci[i].ugibaneCrke.emplace_back(tolower(crka));
				int najd = 0;
				//Izpis uganjenih in neuganjenih crk
				for (int k = 0; k < igralci[i].trenutnoG.length(); k++)
				{
					bool iz = false;
					for (int l = 0; l < igralci[i].ugibaneCrke.size() - 1; l++)
					{
						if (igralci[i].ugibaneCrke[l] == igralci[i].trenutnoG[k]) {
							cout << igralci[i].trenutnoG[k];
							iz = true;
						}
					}
					if (igralci[i].trenutnoG[k] == igralci[i].ugibaneCrke[j]) {
						cout << igralci[i].trenutnoG[k];
						najd++;
					}
					else if (iz == false) cout << "_";
				}
				cout << endl;
				dolGesla = dolGesla - najd;
				if (najd == 0) narobe++;
				if(narobe != -1) cout << endl << scenariji[narobe] << endl;
			}
			else {
				cout << "To crko si ze vpisal, poskuski ponovno.\n";
				j--;
			}
		}

		//Cas se ustavi in vstavi v strukturo
		clock_t end = clock();
		igralci[i].cas = ((double)(end - start)) / CLOCKS_PER_SEC;


		//cout << igralci[i].ime << " je porabil: " << igralci[i].cas << "s\n";

		//St ugibanj se nastavi na velikost vektorja
		//igralci[i].stUgibanj = igralci[i].ugibaneCrke.size();
		//cout << igralci[i].ugibaneCrke.size() << endl;
	}

	//razporeditev(igralci, 5);

	//Izpis igralca z najmanj ugibov
	cout << "Najmanj ugibov: " << igralci[minSt(igralci, 5)].ime << ", stevilo ugibov: " << igralci[minSt(igralci, 5)].ugibaneCrke.size() << endl;


	//Izpis v obliki HTML
	cout << "Izpis v obliki HTML:\n";

	cout << "<table>\n    <tr>\n        <th>Tekmovalec</th><th>Ugibano geslo</th><th>Stevilo ugibanj</th><th>Skupni cas</th>\n    </tr>\n";
	for (int i = 0; i < 5; i++)
	{
		cout << "    <tr>\n       <td>" << igralci[i].ime << "<td/><td>'" << igralci[i].trenutnoG << "'<td/><td>" << igralci[i].ugibaneCrke.size() << "</td><td>" << igralci[i].cas << "s</td>\n    </tr>\n";
	}
	cout << "</table";
}
