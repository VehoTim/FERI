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
	cout << "Hitro uredi dvojno-povezan seznam - izbira" << endl;
	cout << endl;
	cout << "1) Generiraj nakljucno zaporedje" << endl;
	cout << "2) Izpis zaporedja" << endl;
	cout << "3) Preveri urejenost zaporedja" << endl;
	cout << "4) Izpisi vsoto elementov" << endl;
	cout << "5) Uredi" << endl;
	cout << "6) Konec" << endl;
	cout << endl;
	cout << "Izbira: ";
}

//vstavi na konec
void vstaviRep(element*& tail, element* novEl, element*& head) {
	novEl->prev = tail;
	novEl->next = nullptr;
	if (tail != nullptr) tail->next = novEl;
	else head = novEl;

	tail = novEl;
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

void fill(element* &head, element* &tail, int N) {
	srand(time(nullptr));
	element* novEl;
	for (int i = 0; i < N; i++){
		novEl = new element;
		novEl->key = rand();
		vstaviRep(tail, novEl, head);
	}
}

bool preveriZaporedje(element* head, int N) {
	element* tmp = head;
	for (int i = 0; i < N - 1; i++)
	{
		if (tmp->key > tmp->next->key) return false;
		tmp = tmp->next;
	}
	return true;
}

long long vsotaEl(element* head, int N) {
	element* tmp = head;
	long long out = tmp->key;
	for (int i = 0; i < N - 1; i++)
	{
		tmp = tmp->next;
		out += tmp->key;
	}
	return out;
}

element* deli(element* &dno, element* &vrh) {
	int pe = dno->key;
	element* l = dno;
	element* d = vrh;

	bool prekrizala = false;

	while (!prekrizala)
	{
		while (l->key <= pe && l != vrh) {
			l = l->next;
			if (l == d) prekrizala = true;
		}
		while (d->key >= pe && d != dno) {
			d = d->prev;
			if (d == l) prekrizala = true;
		}

		if (!prekrizala) std::swap(l->key, d->key);
	}
	std::swap(dno->key, d->key);
	return d;
}

void quickSort(element* &dno, element*& vrh) {
	element* j;
	if (dno != vrh)
	{
		j = deli(dno, vrh);
		if(dno!=j) quickSort(dno, j->prev);
		if(vrh!=j) quickSort(j->next, vrh);
	}
}

int main(int argc, char* argv[]) {
	//deklaracije spremenljivk
	int izbira;
	int N;

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
			pocistiSeznam(head);
			head = nullptr;
			tail = nullptr;
			cout << "Izberi dolzino zaporedja: ";
			cin >> N;
			fill(head, tail, N);
			break;
		case 2:
			if (tail == nullptr) cout << "Najprej ustvari zaporedje!" << endl;
			else {
				cout << "Zaporedje: ";
				printGlavaRep(head);
			}
			break;
		case 3:
			if (tail == nullptr) cout << "Najprej ustvari zaporedje!" << endl;
			else {
				if (preveriZaporedje(head, N)) cout << "Zaporedje je urejeno";
				else cout << "Zaporedje ni urejeno";
			}
			break;
		case 4:
			if (tail == nullptr) cout << "Najprej ustvari zaporedje!" << endl;
			else cout << vsotaEl(head, N);
			break;
		case 5:
			if (tail == nullptr) cout << "Najprej ustvari zaporedje!" << endl;
			else {
				cout << "Urejanje poteka" << endl;
				start = std::chrono::steady_clock::now();;
				quickSort(head, tail);
				end = std::chrono::steady_clock::now();;

				cout << "Urejanje je trajalo: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << "microsec." << std::endl;
			}
			break;
		case 6:
			return 0;
			break;
		default:
			break;
		}

	} while (true);
}
