#include <iostream>
#include <chrono>

using namespace std;

//struktura za dvojno povezan seznam
struct element {
	int key;
	element* prev, * next;
};

//meni
void printMenu() {
	cout << endl;
	cout << "Dvojno povezan seznam - izbira" << endl;
	cout << endl;
	cout << "1) Iskanje podatka" << endl;
	cout << "2) Vnos podatka v glavo" << endl;
	cout << "3) Vnos podatka za elementom" << endl;
	cout << "4) Vnos podatka za repom" << endl;
	cout << "5) Brisanje podatka" << endl;
	cout << "6) Izpis seznama od glave proti repu" << endl;
	cout << "7) Izpis seznama od repa proti glavi" << endl;
	cout << "8) Testiraj hitrost" << endl;
	cout << "0) Konec" << endl;
	cout << endl;
	cout << "Izbira: ";
}

//funkcija poisce in vrne iskani element v seznamu
element* Iskanje(element* head, int key) {
	if (head == nullptr) {
		cout << "Seznam je prazen!\n";
		return 0;
	}

	element* current = head;

	while (current != nullptr && current->key != key) current = current->next;

	return current;
}

//vstavi na zacetek
void vstaviGlavo(element*& head, element* novEl, element*& tail) {
	novEl->next = head;
	novEl->prev = nullptr;
	if (head != nullptr) head->prev = novEl;
	else tail = novEl;

	head = novEl;

	//cout << "Vstavljen element: " << Iskanje(head, head->key)->key << endl;;
}

//vstavi za dolocenim elementom
void vstaviZa(element*& elem, element* novEl, element*& head, element*& tail) {
	novEl->prev = elem;
	novEl->next = elem->next;
	elem->next = novEl;

	if (novEl->next != nullptr)	novEl->next->prev = novEl;
	else tail = novEl;

	cout << "Vstavljen element: " << Iskanje(head, novEl->key)->key << endl;;
}

//vstavi na konec
void vstaviRep(element*& tail, element* novEl, element*& head) {
	novEl->prev = tail;
	novEl->next = nullptr;
	if (tail != nullptr) tail->next = novEl;
	else head = novEl;

	tail = novEl;

	cout << "Vstavljen element: " << Iskanje(head, tail->key)->key << endl;;
}

//brisi dolocen element
void brisi(element*& head, element*& elem, element*& tail) {
	cout << "Izbrisan element: " << Iskanje(head, elem->key)->key << endl;

	if (elem->prev == nullptr && elem->next == nullptr)
	{
		head = nullptr;
		tail = nullptr;
	}
	else {
		if (elem->prev != nullptr) elem->prev->next = elem->next;

		//brisanje glave
		else {
			head = elem->next;
			head->prev;
		}

		if (elem->next != nullptr) elem->next->prev = elem->prev;

		//brisanje repa
		else {
			tail = elem->prev;
			tail->next = nullptr;
		}
	}

	delete elem;
}

//izpis od glave do repa
void printGlavaRep(element* head) {
	element* current = head;

	while (current != nullptr) {
		cout << current->key << " ";
		current = current->next;
	}

	cout << endl;
}

//izpis od repa do glave
void printRepGlava(element* tail) {
	element* current = tail;

	while (current != nullptr) {
		cout << current->key << " ";
		current = current->prev;
	}

	cout << endl;
}

//pocisti vse elemente seznama
void pocistiSeznam(element*& head) {
	element* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;

		if (temp->prev) temp->prev = nullptr;
		if (temp->next) temp->next = nullptr;
	}
}

//sesteje vrednosti v seznamu
void vsotaSeznam(element* head) {
	element* temp = new element;
	temp = head;
	long long skup = 0;
	while (temp != nullptr)
	{
		skup += temp->key;
		temp = temp->next;
	}
	cout << "Skupaj: " << skup << endl;
	delete temp;
	temp = nullptr;
}

//sesteje vrednosti v polju
void vsotaPolje(int* polje, int N) {
	long long skup = 0;
	for (int i = 0; i < N; i++)
	{
		skup += polje[i];
	}
	cout << "Skupaj: " << skup << endl;
}

int main(int argc, char* argv[]) {

	//deklaracije spremenljivk
	int izbira;
	int key;
	int ind;
	int N;
	element* novEl;
	element* temp;
	int* polje;
	//int* polje2;


	//glava in rep seznama
	element* head = nullptr;
	element* tail = nullptr;

	auto start = std::chrono::steady_clock::now();;
	auto end = std::chrono::steady_clock::now();;

	do
	{
		//izpis menija ob vsakem zacetku
		printMenu();
		cin >> izbira;

		switch (izbira)
		{
		case 1:
			cout << "Vpisi kljuc iskanega elementa: ";
			cin >> key;
			if (Iskanje(head, key) != nullptr)
			{
				cout << "Iskani element: " << Iskanje(head, key)->key << endl;
			}
			else cout << "Takega elementa ni\n";

			break;
		case 2:
			cout << "Vpisi kljuc vnosnega elementa: ";
			cin >> key;
			novEl = new element;
			novEl->key = key;
			vstaviGlavo(head, novEl, tail);
			break;
		case 3:
			cout << "Vpisi za katerim zelis vnesti: ";
			cin >> ind;
			cout << "Vpisi kljuc vnosnega elementa: ";
			cin >> key;
			temp = new element;
			temp = Iskanje(head, ind);
			if (temp != nullptr) {
				novEl = new element;
				novEl->key = key;
				vstaviZa(temp, novEl, head, tail);
			}
			else cout << "Ta element ne obstaja\n";
			break;
		case 4:
			cout << "Vpisi kljuc vnosnega elementa: ";
			cin >> key;
			novEl = new element;
			novEl->key = key;
			vstaviRep(tail, novEl, head);
			break;
		case 5:
			cout << "Vpisi element, ki ga zelis izbrisati: ";
			cin >> ind;
			temp = new element;
			temp = Iskanje(head, ind);
			if (temp != nullptr) brisi(head, temp, tail);
			else cout << "Ta element ne obstaja\n";
			break;
		case 6:
			if (head != nullptr) printGlavaRep(head);
			else cout << "\nSeznam je prazen\n";
			break;
		case 7:
			if (head != nullptr) printRepGlava(tail);
			else cout << "\nSeznam je prazen\n";
			break;
		case 8:
			cout << "Koliko elementov: ";
			cin >> N;
			//1
			start = std::chrono::steady_clock::now();
			pocistiSeznam(head);
			for (int i = 1; i <= N; i++)
			{
				novEl = new element;
				novEl->key = i;
				vstaviGlavo(head, novEl, tail);
			}
			end = std::chrono::steady_clock::now();
			cout << "Cas trajanja vstavljanja v seznam: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"ms." << std::endl;

			//2
			start = std::chrono::steady_clock::now();
			vsotaSeznam(head);
			end = std::chrono::steady_clock::now();
			cout << "Cas trajanja sestevanja vsote seznama: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"ms." << std::endl;
			//3
			start = std::chrono::steady_clock::now();
			polje = new int[N];
			for (int i = 1; i <= N; i++)
			{
				for (int j = i; j > 0; j--) {
					polje[j] = polje[j - 1];
				}
				polje[0] = i;
			}
			end = std::chrono::steady_clock::now();
			cout << "Cas trajanja vstavljanja v polje in premikanja v desno: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"ms." << std::endl;
			//4
			start = std::chrono::steady_clock::now();
			vsotaPolje(polje, N);
			end = std::chrono::steady_clock::now();
			cout << "Cas trajanja sestevanja vsote polje: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"ms." << std::endl;
			//5
			start = std::chrono::steady_clock::now();
			polje = new int[N];
			for (int i = 0; i < N; i++)
			{
				polje[i] = i + 1;
			}
			end = std::chrono::steady_clock::now();
			cout << "Cas trajanja vstavljanja v polje: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"ms." << std::endl;

			delete[] polje;
			polje = nullptr;
			pocistiSeznam(head);

			break;
		case 0:
			return 0;
			break;
		default:
			break;
		}

	} while (true);
}
