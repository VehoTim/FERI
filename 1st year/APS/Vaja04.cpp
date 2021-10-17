#include <iostream>

using namespace std;

struct Vozlisce{
	int key;
	Vozlisce* oce;
	Vozlisce* leviSin;
	Vozlisce* desniSin;
};

void printMeni() {
	cout << "Binarno iskalno drevo - izbira:\n" << endl;
	cout << "1) Vnos podatka" << endl;
	cout << "2) Urejen izpis vrednosti" << endl;
	cout << "3) Izpis povezav" << endl;
	cout << "4) Iskanje" << endl;
	cout << "5) Poisci minimum and maksimum" << endl;
	cout << "6) Poisci predhnodnika in naslednika" << endl;
	cout << "7) Brisi vrednost" << endl;
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

void vstavi(Vozlisce* &T, int k) {
	bool nadaljuj = true;

	Vozlisce* y = nullptr;
	Vozlisce* x = T;

	while (x != nullptr)
	{
		y = x;
		if (k < x->key) x = x->leviSin;
		else if (k > x->key) x = x->desniSin;
		else {
			cout << "Napaka pri vnasanju!\n";
			nadaljuj = false;
			break;
		}
	}

	if (nadaljuj)
	{
		Vozlisce* z = new Vozlisce();
		z->key = k;
		z->oce = y;

		if (y == nullptr) T = z;
		else {
			if (z->key < y->key) y->leviSin = z;
			else y->desniSin = z;
		}
	}
}

void printUrejeno(Vozlisce* x) {
	if (x != nullptr)
	{
		printUrejeno(x->leviSin);
		cout << x->key << " ";
		printUrejeno(x->desniSin);
	}
}

void printVsePovezave(Vozlisce* x) {
	if (x->leviSin != nullptr)
	{
		cout << x->key << "->" << x->leviSin->key << " ";
		printVsePovezave(x->leviSin);
	}
	if (x->desniSin != nullptr)
	{
		cout << x->key << "->" << x->desniSin->key << " ";
		printVsePovezave(x->desniSin);
	}
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

Vozlisce* predhnodik(Vozlisce* x) {
	if (x->leviSin != nullptr) return max(x->leviSin);

	Vozlisce* y = x->oce;
	while (y != nullptr && x == y->leviSin)
	{
		x = y;
		y = y->oce;
	}
	return y;
}

void brisiScenarij1_2(Vozlisce* &T, Vozlisce* &y) {
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

void brisi(Vozlisce* &T, Vozlisce* &z) {
	Vozlisce* y;
	if (z->leviSin == nullptr || z->desniSin == nullptr) brisiScenarij1_2(T, z);
	else {
		y = naslednik(z);
		int vrednost = y->key;
		brisiScenarij1_2(T, y);
		z->key = vrednost;
	}
}

int main()
{
	int izbira;
	int key;
	Vozlisce* T = nullptr;

	do
	{
		//izpis menija ob vsakem zacetku
		printMeni();
		cin >> izbira;

		switch (izbira)
		{
		case 1:
			cout << "Katero vrednost zelis vstaviti: ";
			cin >> key;
			vstavi(T, key);
			cout << endl;
			break;
		case 2:
			if (T != nullptr)
			{
				printUrejeno(T);
				cout << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 3:
			if (T != nullptr)
			{
				printVsePovezave(T);
				cout << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 4:
			if (T != nullptr)
			{
				cout << "Vnesi iskano stevilo: ";
				cin >> key;
				if (poisci(T, key) != nullptr) cout << "Najden kljuc: " << poisci(T, key)->key << endl;
				else cout << "Kljuc ni bil najden\n" << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 5:
			if (T != nullptr)
			{
				cout << "Min. vrednost: " << min(T)->key << endl;
				cout << "Max. vrednost: " << max(T)->key << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 6:
			if (T != nullptr)
			{
				cout << "Vpisi kljuc od katerega predhodnika in naslednika zelis najti: ";
				cin >> key;
				if (poisci(T, key) != nullptr)
				{
					cout << "Predhodnik: ";
					if (predhnodik(poisci(T, key)) != nullptr)
						cout << predhnodik(poisci(T, key))->key << endl;
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
		case 7:
			if (T != nullptr)
			{
				cout << "Vpisi kljuc, ki ga zelis izbrisati: ";
				cin >> key;
				Vozlisce* z = poisci(T, key);
				if (poisci(T, key) != nullptr) brisi(T, z);
				else cout << "Prislo je do napake";
				cout << endl;
			}
			else cout << "Drevo je prazno" << endl;
			break;
		case 8:
			return 0;
			break;
		default:
			break;
		}

		//izpis drevesa
		if (izbira != 2 && T != nullptr)
		{
			cout << "Trenutno drevo: ";
			printUrejeno(T);
			cout << endl << endl;
		}
	} while (true);
}
