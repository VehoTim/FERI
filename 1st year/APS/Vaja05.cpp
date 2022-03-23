#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

struct Vozlisce {
	int key;	//datum yyyymmdd
	Vozlisce* oce = nullptr;
	Vozlisce* leviSin = nullptr;
	Vozlisce* desniSin = nullptr;
	vector<string> seznam;
};

void printMeni() {
	cout << "Filmi - izbira:\n" << endl;
	cout << "1) Vnos filma" << endl;
	cout << "2) Urejen izpis filmov" << endl;
	cout << "3) Iskanje po datumu izdaje" << endl;
	cout << "4) Poisci minimum and maksimum" << endl;
	cout << "5) Poisci predhnodnika in naslednika" << endl;
	cout << "6) Brisi datum" << endl;
	cout << "7) Nalaganje filmov iz datoteke" << endl;
	cout << "8) Konec\n" << endl;

	cout << "Izbira: ";
}

Vozlisce* poisci(Vozlisce* x, int k) {
	//ce je glava prazna ali ce je glava iskana vrednost
	if (x == nullptr || x->key == k) return x;
	//pomaknemo naprej
	else
	{
		if (k < x->key) return poisci(x->leviSin, k);
		else return poisci(x->desniSin, k);
	}
}

void vstavi(Vozlisce*& T, int k, string ime) {
	Vozlisce* y = nullptr;
	Vozlisce* x = T;

	while (x != nullptr)
	{
		y = x;
		if (k < x->key) x = x->leviSin;
		else if (k > x->key) x = x->desniSin;
		else {
			x->seznam.insert(x->seznam.begin(), ime);
			return;
		}
	}

	Vozlisce* z = new Vozlisce();
	z->key = k;
	z->seznam.insert(z->seznam.begin(), ime);
	z->oce = y;

	if (y == nullptr) T = z;
	else {
		if (z->key < y->key) y->leviSin = z;
		else y->desniSin = z;
	}
}

void printUrejeno(Vozlisce* x) {
	if (x != nullptr)
	{
		printUrejeno(x->leviSin);
		cout << endl << x->key << ": " << endl;
		for (string s : x->seznam) {
			cout << " " << s << endl;
		}
		printUrejeno(x->desniSin);
	}
}

void printDatum(Vozlisce* T, int key) {
	auto start = std::chrono::steady_clock::now();;
	auto end = std::chrono::steady_clock::now();;

	start = std::chrono::steady_clock::now();

	Vozlisce* tmp = poisci(T, key);

	end = std::chrono::steady_clock::now();

	cout << "Cas trajanja iskanja: " << std::chrono::duration_cast<std::chrono::microseconds>
		(end - start).count() <<
		"microsec." << std::endl;

	if (tmp != nullptr)
	{
		cout << endl << tmp->key << ": " << endl;
		for (string s : T->seznam) {
			cout << " " << s << endl;
		}
	}
	else cout << "Iskani datum nima filmov" << endl;
}

Vozlisce* min(Vozlisce* T) {
	Vozlisce* x = T;
	while (x->leviSin != nullptr) x = x->leviSin;
	return x;
}

Vozlisce* max(Vozlisce* T) {
	Vozlisce* x = T;
	while (x->desniSin != nullptr) x = x->desniSin;
	return x;
}

Vozlisce* naslednik(Vozlisce* x) {
	if (x->desniSin != nullptr) return min(x->desniSin);

	Vozlisce* y = x->oce;
	while (y != nullptr && x == y->desniSin)
	{
		x = y;
		y = y->oce;
	}
	return y;
}

Vozlisce* predhodnik(Vozlisce* x) {
	if (x->leviSin != nullptr) return max(x->leviSin);

	Vozlisce* y = x->oce;
	while (y != nullptr && x == y->leviSin)
	{
		x = y;
		y = y->oce;
	}
	return y;
}

void brisiScenarij1_2(Vozlisce*& T, Vozlisce*& y) {
	Vozlisce* x;
	if (y->leviSin != nullptr) x = y->leviSin;
	else x = y->desniSin;

	if (x != nullptr) x->oce = y->oce;

	if (y->oce == nullptr) T = x;
	else
	{
		if (y == y->oce->leviSin) y->oce->leviSin = x;
		else y->oce->desniSin = x;
	}

	delete y;
	y = nullptr;
}

void brisi(Vozlisce*& T, Vozlisce*& z) {
	Vozlisce* y;
	z->seznam.empty();
	if (z->leviSin == nullptr || z->desniSin == nullptr) brisiScenarij1_2(T, z);
	else {
		y = naslednik(z);
		int datum = y->key;
		vector<string> seznam = y->seznam;
		brisiScenarij1_2(T, y);
		z->key = datum;
		z->seznam = seznam;
	}
}

void brisiVse(Vozlisce*& T) {
	while (T != nullptr){
		brisi(T, T);
	}
}

int main()
{
	int izbira;
	int izbira2;
	int key;
	string ime;
	Vozlisce* T = nullptr;

	do
	{
		//izpis menija ob vsakem zacetku
		printMeni();
		cin >> izbira;

		switch (izbira)
		{
		case 1:
			cout << "Vpisi datum filma: ";
			cin >> key;
			cout << "Vpisi ime filma: ";
			cin.ignore();
			getline(cin, ime);
			vstavi(T, key, ime);
			cout << endl;
			break;
		case 2:
			if (T != nullptr)
			{
				printUrejeno(T);
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 3:
			cout << "Vpisi iskani datum: ";
			cin >> key;
			if (T != nullptr)
			{
				printDatum(T, key);
				cout << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 4:
			if (T != nullptr)
			{
				cout << "Min. vrednost: " << min(T)->key << endl;
				cout << "Max. vrednost: " << max(T)->key << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 5:
			if (T != nullptr)
			{
				cout << "Vpisi kljuc od katerega predhodnika in naslednika zelis najti: ";
				cin >> key;
				if (poisci(T, key) != nullptr)
				{
					cout << "Predhodnik: ";
					if (predhodnik(poisci(T, key)) != nullptr)
						cout << predhodnik(poisci(T, key))->key << endl;
					else cout << "/" << endl;
					cout << "Naslednik: ";
					if (naslednik(poisci(T, key)) != nullptr)
						cout << naslednik(poisci(T, key))->key << endl;
					else cout << "/" << endl;
				}
				else cout << "Prislo je do napake" << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 6:
			if (T != nullptr)
			{
				cout << "Vpisi datum, ki ga zelis izbrisati: ";
				cin >> key;
				Vozlisce* z = poisci(T, key);
				if (poisci(T, key) != nullptr) brisi(T, z);
				else cout << "Prislo je do napake";
				cout << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		/*case 7:
			break;*/
		case 8:
			return 0;
			break;
		default:
			break;
		}

		if (izbira == 7)
		{
			cout << "Brisem..." << endl;
			brisiVse(T);
			string lists[4]{"IMDB_date_name_mini.list", "IMDB_date_name_mini_sorted.list", "IMDB_date_name_full.list", "IMDB_date_name_full_sorted.list"};
			cout << "\nSeznam datotek:" << endl;
			cout << "1) IMDB_date_name_mini.list" << endl;
			cout << "2) IMDB_date_name_mini_sorted.list" << endl;
			cout << "3) IMDB_date_name_full.list" << endl;
			cout << "4) IMDB_date_name_full_sorted.list" << endl;
			cout << endl << "Izberi datoteko: ";
			cin >> izbira2;
			if (izbira2 > 0 && izbira2 < 5)
			{
				auto start = std::chrono::steady_clock::now();;
				auto end = std::chrono::steady_clock::now();;

				start = std::chrono::steady_clock::now();

				ifstream in(lists[izbira2 - 1]);
				int N;
				in >> N;
				for (int i = 0; i < N; i++) {
					in >> key;
					getline(in, ime, '\n');
					vstavi(T, key, ime);
					if (i % 1000 == 0) {
						cout << "*" << flush;
					}
				}
				cout << endl;

				end = std::chrono::steady_clock::now();

				cout << "Cas trajanja vstavljanja: " << std::chrono::duration_cast<std::chrono::microseconds>
					(end - start).count() <<
					"microsec." << std::endl;

				start = std::chrono::steady_clock::now();

				poisci(T, 20121022);
				poisci(T, 20090908);
				poisci(T, 20090310);
				poisci(T, 20060917);
				poisci(T, 19970924);

				end = std::chrono::steady_clock::now();

				cout << "Cas trajanja iskanja: " << std::chrono::duration_cast<std::chrono::microseconds>
					(end - start).count() <<
					"microsec." << std::endl;

			}
			else cout << "Napacna izbira!" << endl << endl;
		}
	} while (true);

	brisiVse(T);
}
