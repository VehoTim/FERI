#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;

void printMenu() {
	cout << "Bellman-Fordov algoritem - izbira:\n" << endl;
	cout << "1) Preberi graf iz datoteke\n";
	cout << "2) Generiraj nakljucni graf\n";
	cout << "3) Pozeni algoritem\n";
	cout << "4) Izpisi najkrajso pot\n";
	cout << "5) Konec\n" << endl;
	cout << "\nIzbira: ";
}

struct Vozlisce {
	int predhodnik;
	int cena_poti;
};

Vozlisce* bellmanFord(Vozlisce* &G, int s, int size, int** sosedi){
	for (int i = 0; i < size; i++)
	{
		G[i].cena_poti = 2000000000;
		G[i].predhodnik = -1;
	}
	G[s].cena_poti = 0;
	G[s].predhodnik = -1;
	for (int i = 0; i < size - 1; i++)
	{
		for (int u = 0; u < size; u++)
		{
			for (int v = 0; v < size; v++)
			{
				if (u != v && (G[u].cena_poti + sosedi[u][v] < G[v].cena_poti)) {
					G[v].cena_poti = G[u].cena_poti + sosedi[u][v];
					G[v].predhodnik = u;
				}
			}
		}
	}
	
	for (int u = 0; u < size; u++)
	{
		for (int v = 0; v < size; v++)
		{	
			if (u != v && G[u].cena_poti + sosedi[u][v] < G[v].cena_poti) return nullptr;
		}
	}
	return G;
}

void izpisPoti(Vozlisce* G, int s, int v) {
	if (v == s) {
		cout << "Pot je: \n" << v + 1 /*<< ", predhodnik: " << G[v].predhodnik*/ << ", cena: " << G[v].cena_poti << "; ";
	}
	else {
		if (G[v].predhodnik == -1) cout << "Med " << s + 1 << " in " << v + 1 << " ni poti!";
		else {
			izpisPoti(G, s, G[v].predhodnik);
			cout << v + 1 /*<< ", predhodnik: " << G[v].predhodnik*/ << ", cena: " << G[v].cena_poti << "; ";
		}
	}
	cout << endl;
}

int main()
{
	int steviloVozlisc;
	int cena;
	int** sosedi = nullptr;
	Vozlisce* V = nullptr;
	bool nadaljuj = true;
	int izbira, iskanoVozlisce = -1, ciljnoVozlisce;
	string path;

	//case 2
	int v1, v2;
	bool n1, n2;

	ifstream f;

	auto start = std::chrono::steady_clock::now();;
	auto end = std::chrono::steady_clock::now();;

	do
	{
		printMenu();
		cin >> izbira;
		switch (izbira) {
		case 1:
			cout << "Vpisi ime datoteke: ";
			cin.ignore();
			getline(cin, path);
			f.open(path);

			f >> steviloVozlisc;

			//Izdelava matrike
			sosedi = new int* [steviloVozlisc];
			for (int i = 0; i < steviloVozlisc; i++) {
				sosedi[i] = new int[steviloVozlisc];
				for (int j = 0; j < steviloVozlisc; j++)
				{
					sosedi[i][j] = 0;
				}
			}
			//----------------

			//Izdelava polja vozlisc
			V = new Vozlisce[steviloVozlisc];
			for (int i = 0; i < steviloVozlisc; i++)
			{
				V[i].predhodnik = -1;
				V[i].cena_poti = INT_MAX;
			}

			//Vnos v matrike sosedov
			for (int i = 0; i < steviloVozlisc; i++)
			{
				for (int j = 0; j < steviloVozlisc; j++)
				{
					f >> cena;
					sosedi[i][j] = cena;
				}
			}

			//Izpis tabele sosednosti
			/*for (int i = 0; i < stevilo_vozlisc; i++)
			{
				for (int j = 0; j < stevilo_vozlisc; j++)
				{
					cout << sosedi[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;*/

			f.close();

			cout << endl << "Stevilo prebranih vozlisc: " << steviloVozlisc << endl;
			break;
		case 2:
			do {
				cout << "Vpisi stevilo vozlisc (do 1500): ";
				cin >> steviloVozlisc;
			} while (steviloVozlisc > 1500 || steviloVozlisc < 0);
			//Izdelava polja vozlisc
			V = new Vozlisce[steviloVozlisc];
			for (int i = 0; i < steviloVozlisc; i++)
			{
				V[i].predhodnik = -1;
				V[i].cena_poti = INT_MAX;
			}
			//Izdelava matrike sosedov
			srand(time(nullptr));
			sosedi = new int* [steviloVozlisc];
			for (int i = 0; i < steviloVozlisc; i++) {
				sosedi[i] = new int[steviloVozlisc];
				for (int j = 0; j < steviloVozlisc; j++)
				{
					if (i == j) sosedi[i][j] = 0;
					else sosedi[i][j] = rand() % 10000;
				}
			}
			break;
		case 3:
			cout << "Vpisi izhodiscno vozlisce: ";
			cin >> iskanoVozlisce;
			start = std::chrono::steady_clock::now();;
			V = bellmanFord(V, iskanoVozlisce - 1, steviloVozlisc, sosedi);
			end = std::chrono::steady_clock::now();;
			cout << "Iskanje poti je trajalo: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << "microsec." << std::endl;
			break;
		case 4:
			if (iskanoVozlisce != -1) {
				cout << "Vpisi koncno vozlisce: ";
				cin >> ciljnoVozlisce;
				izpisPoti(V, iskanoVozlisce - 1, ciljnoVozlisce - 1);
			}
			else cout << "Najprej izberi izhodiscno vozlisce" << endl;
			break;
		case 5:
			nadaljuj = false;
			break;
		default:
			break;
		}
	} while (nadaljuj);
}
