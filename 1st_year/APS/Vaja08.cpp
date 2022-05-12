#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <chrono>
#include <sstream>

using namespace std;

bool jeStevilo(const string& s) {
	for (char const& c : s) if (isdigit(c) == 0) return false;
	return true;
}

void printMeni() {
	cout << "Iskanje v globino in sirino - izbira:\n" << endl;
	cout << "1) Preberi graf iz datoteke\n";
	cout << "2) Pozeni iskanje v globino iz vozlisca s do d\n";
	cout << "3) Pozeni iskanje v sirino iz vozlisca s do d\n";
	cout << "4) Izpis seznama vozlisc\n";
	cout << "5) Konec\n" << endl;
	cout << "Izbira: ";
}

struct Vozlisce {
	int predhodnik;
	int dolzina;
	int status;
	int indeks;
	string ime;
};

void iskanjeVGlobino(Vozlisce*& G, int s, int d, int** sosedi, int size) {
	vector<Vozlisce> sklad;
	for (int i = 0; i < size; i++)
	{
		if (i != s) {
			G[i].status = 0;
			G[i].dolzina = INT_MAX;
			G[i].predhodnik = -1;
		}
	}

	G[s].status = 1;
	G[s].dolzina = 0;
	G[s].predhodnik = -1;
	sklad.push_back(G[s]);

	while (!(sklad.empty())) {
		Vozlisce v = sklad.back();
		sklad.pop_back();
		if (v.indeks == d) return;
		for (int i = 0; i < size; i++)
		{
			if (sosedi[v.indeks][i] > 0) {
				if (G[i].status == 0) {
					G[i].status = 1;
					G[i].dolzina = v.dolzina + 1;
					G[i].predhodnik = v.indeks;
					sklad.push_back(G[i]);
				}
			}
		}
		v.status = 2;
	}
}

void iskanjeVSirino(Vozlisce*& G, int s, int d, int** sosedi, int size) {
	vector<Vozlisce> vrsta;
	for (int i = 0; i < size; i++)
	{
		G[i].status = 0;
		G[i].dolzina = INT_MAX;
		G[i].predhodnik = -1;
	}

	G[s].status = 1;
	G[s].dolzina = 0;
	G[s].predhodnik = -1;
	vrsta.push_back(G[s]);

	while (!(vrsta.empty())) {
		Vozlisce v = vrsta.front();
		vrsta.erase(vrsta.begin());
		if (v.indeks == d) return;
		for (int i = 0; i < size; i++)
		{
			if (sosedi[v.indeks][i] > 0) {
				if (G[i].status == 0) {
					G[i].status = 1;
					G[i].dolzina = v.dolzina + 1;
					G[i].predhodnik = v.indeks;
					vrsta.push_back(G[i]);
				}
			}
		}
		v.status = 2;
	}
}

void izpisPoti(Vozlisce* G, int s, int v) {
	if (v == s) {
		cout << "Pot je: \n" << G[v].ime << ", predhodnik: " << G[v].predhodnik << ", cena: " << G[v].dolzina << "; ";
	}
	else {
		if (G[v].predhodnik == -1) cout << "Med " + G[s].ime << " in " << G[v].ime << " ni poti!";
		else {
			izpisPoti(G, s, G[v].predhodnik);
			cout << G[v].ime << ", predhodnik: " << G[G[v].predhodnik].ime << ", cena: " << G[v].dolzina << "; ";
		}
	}
	cout << endl;
}

int main()
{
	int stevilo_vozlisc, stevilo_povezav;
	int indeksV1, indeksV2, cena;
	bool nadaljuj = true;
	int izbira;
	string preberiIzbiro;
	int** sosedi = nullptr;
	string s, d;
	Vozlisce* V = nullptr;

	auto start = std::chrono::steady_clock::now();;
	auto end = std::chrono::steady_clock::now();;

	//ifstream f("grafBig.txt");
	ifstream f("graf.txt");

	while (nadaljuj) {
		printMeni();
		while (getline(cin, preberiIzbiro)) {
			stringstream ss(preberiIzbiro);
			if (ss >> izbira) {
				if (ss.eof()) break;
			}
			//cout << "Napaka pri vnosu!" << endl;
		}
		switch (izbira)
		{
		case 1:
			f >> stevilo_vozlisc;
			f >> stevilo_povezav;

			//Izdelava matrike
			sosedi = new int* [stevilo_vozlisc];
			for (int i = 0; i < stevilo_vozlisc; i++) {
				sosedi[i] = new int[stevilo_vozlisc];
			}

			for (int i = 0; i < stevilo_vozlisc; i++)
			{
				for (int j = 0; j < stevilo_vozlisc; j++)
				{
					sosedi[i][j] = 0;
				}
			}
			//----------------

			//Izdelava vozlisc
			V = new Vozlisce[stevilo_vozlisc];
			for (int i = 0; i < stevilo_vozlisc; i++)
			{
				V[i].indeks = i;
				V[i].ime = "vozlisce" + to_string(V[i].indeks + 1);
			}


			//Vnos v matrike sosedov
			for (int i = 0; i < stevilo_povezav; i++)
			{
				f >> indeksV1 >> indeksV2 >> cena;
				sosedi[indeksV1 - 1][indeksV2 - 1] = cena;
				sosedi[indeksV2 - 1][indeksV1 - 1] = cena;
			}

			/*for (int i = 0; i < stevilo_vozlisc; i++)
			{
				for (int j = 0; j < stevilo_vozlisc; j++)
				{
					cout << sosedi[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;*/
			break;
		case 2:
			if (sosedi != nullptr) {
				do {
					cout << "Vpisi ime izhodiscnega vozlisca: ";
					cin >> s;
					if ((s.substr(0, 8) != "vozlisce") || (s.length() < 9) || !(jeStevilo(s.substr(8))) || (stoi(s.substr(8)) > stevilo_vozlisc)) cout << "napaka!\n";
					else break;
				} while (true);
				do {
					cout << "Vpisi ime ciljnega vozlisca: ";
					cin >> d;
					if ((d.substr(0, 8) != "vozlisce") || (d.length() < 9) || !(jeStevilo(d.substr(8))) || (stoi(d.substr(8)) > stevilo_vozlisc)) cout << "napaka!\n";
					else break;
				} while (true);

				start = std::chrono::steady_clock::now();;
				iskanjeVGlobino(V, stoi(s.substr(8)) - 1, stoi(d.substr(8)) - 1, sosedi, stevilo_vozlisc);
				end = std::chrono::steady_clock::now();;

				cout << endl;
				izpisPoti(V, stoi(s.substr(8)) - 1, stoi(d.substr(8)) - 1);
				cout << endl;
				cout << "Iskanje je trajalo: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << "microsec." << std::endl;
				cout << endl;
			}
			else cout << "Najprej izberi graf!\n";
			break;
		case 3:
			if (sosedi != nullptr) {
				if (sosedi != nullptr) {
					do {
						cout << "Vpisi ime izhodiscnega vozlisca: ";
						cin >> s;
						if ((s.substr(0, 8) != "vozlisce") || (s.length() < 9) || !(jeStevilo(s.substr(8))) || (stoi(s.substr(8)) > stevilo_vozlisc)) cout << "napaka!\n";
						else break;
					} while (true);
					do {
						cout << "Vpisi ime ciljnega vozlisca: ";
						cin >> d;
						if ((d.substr(0, 8) != "vozlisce") || (d.length() < 9) || !(jeStevilo(d.substr(8))) || (stoi(d.substr(8)) > stevilo_vozlisc)) cout << "napaka!\n";
						else break;
					} while (true);

					start = std::chrono::steady_clock::now();;
					iskanjeVSirino(V, stoi(s.substr(8)) - 1, stoi(d.substr(8)) - 1, sosedi, stevilo_vozlisc);
					end = std::chrono::steady_clock::now();;

					cout << endl;
					izpisPoti(V, stoi(s.substr(8)) - 1, stoi(d.substr(8)) - 1);
					cout << endl;
					cout << "Iskanje je trajalo: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << "microsec." << std::endl;
					cout << endl;
				}
				else cout << "Najprej izberi graf!\n";
				break;
		case 4:
			if (V != nullptr) {
				for (int i = 0; i < stevilo_vozlisc; i++)
				{
					cout << "Indeks: " << V[i].indeks << ", ime: " << V[i].ime << endl;
				}
			}
			else cout << "Najprej napolni seznam!\n";
			break;
		case 5:
			nadaljuj = false;
			break;
		default:
			break;
			}
		}
	}

	//Brisanje
	for (int i = 0; i < stevilo_vozlisc; i++) {
		delete[]sosedi[i];
	}
	delete[]sosedi;
	delete[]V;
}
