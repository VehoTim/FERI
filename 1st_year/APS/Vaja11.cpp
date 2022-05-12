#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <chrono>

using namespace std;

struct pot {
	int iz_vozlisca;
	int v_vozlisce;
	int cena;
	vector<bool> mnozica; //S
};

void printMeni() {
	cout << "Trgovski potnik - izbira :\n" << endl;
	cout << "1) Preberi matriko" << endl;
	cout << "2) Resi problem trgovskega potnika" << endl;
	cout << "3) Izpisi dobljen seznam nivojev" << endl;
	cout << "4) Rekonstrukcija poti" << endl;
	cout << "5) Izhod" << endl;
	cout << "Izbira: ";
}

list<pot> vstaviPrvaVozlisca(int** sosedi, int N){
	list<pot> nivo;
	pot cur;
	vector<bool> mnozica(N - 1, false);
	for (int i = 1; i < N; i++)
	{	
		cur.cena = sosedi[i][0];
		cur.iz_vozlisca = i;
		cur.v_vozlisce = 0;
		cur.mnozica = mnozica;
		nivo.push_back(cur);
	}
	return nivo;
}

void napraviSeznam(int** sosedi, int N, int vozlisce, stack<list<pot>> &nivoji, list<pot> &nivo) {
	list<pot> prev = nivoji.top();
	pot cur;
	bool erased;
	bool found;
	while (!prev.empty())
	{
		erased = 0;
		found = 0;
		pot prevPot = prev.back();
		if (!prevPot.mnozica[vozlisce - 1] && vozlisce != prevPot.iz_vozlisca) {
			cur.iz_vozlisca = vozlisce;
			cur.v_vozlisce = prevPot.iz_vozlisca;
			cur.cena = sosedi[cur.iz_vozlisca][cur.v_vozlisce] + prevPot.cena;
			cur.mnozica = prevPot.mnozica;
			cur.mnozica[cur.v_vozlisce - 1] = true;
			for (auto itr = nivo.cbegin(); itr != nivo.end(); itr++)
			{
				if (itr->iz_vozlisca == cur.iz_vozlisca && itr->mnozica == cur.mnozica) {
					found = 1;
					if (itr->cena > cur.cena) {
						nivo.erase(itr--);
						erased = 1;
					}
				}
			}
			if (erased || !found) nivo.push_back(cur);
		}
		prev.pop_back();
	}
}

list<pot> koncajSeznam(int** sosedi, int N, stack<list<pot>>& nivoji) {
	list<pot> nivo;
	list<pot> prev = nivoji.top();
	pot cur;
	pot max;
	max.cena = INT_MAX;
	bool erased;
	bool found;
	while (!prev.empty()) {
		erased = found = 0;
		pot prevPot = prev.back();
		cur.iz_vozlisca = 0;
		cur.v_vozlisce = prevPot.iz_vozlisca;
		cur.cena = sosedi[cur.iz_vozlisca][cur.v_vozlisce] + prevPot.cena;
		cur.mnozica = prevPot.mnozica;
		cur.mnozica[cur.v_vozlisce - 1] = true;
		if (max.cena > cur.cena) {
			max = cur;
		}
		prev.pop_back();
	}
	nivo.push_back(max);
	return nivo;
}

stack<list<pot>> potnik(int** sosedi, int N) {
	stack<list<pot>> nivoji;
	list<pot> nivo = vstaviPrvaVozlisca(sosedi, N);
	list<pot> cur;
	nivoji.push(nivo);

	for (int i = 1; i < N - 1; i++)
	{
		nivo.clear();
		for (int j = 1; j < N; j++)
		{
			napraviSeznam(sosedi, N, j, nivoji, nivo);
		}
		nivoji.push(nivo);
	}
	nivo = koncajSeznam(sosedi, N, nivoji);
	nivoji.push(nivo);
	return nivoji;
}

vector<pot> rekonstrukcijaPoti(stack<list<pot>> nivoji) {
	vector<pot> seznamPoti;
	stack<list<pot>> tmpNivoji = nivoji;
	list<pot> curNivo = tmpNivoji.top();
	tmpNivoji.pop();
	pot potOd = curNivo.back();
	pot potDo;
	vector<bool> mnozica;
	seznamPoti.push_back(potOd);
	while (!tmpNivoji.empty()) {
		curNivo = tmpNivoji.top();
		potOd = seznamPoti.back();
		mnozica = potOd.mnozica;
		mnozica[potOd.v_vozlisce - 1] = false;
		while (!curNivo.empty()) {
			potDo = curNivo.back();
			if (potOd.v_vozlisce == potDo.iz_vozlisca && potDo.mnozica == mnozica) {
				seznamPoti.push_back(potDo);
				break;
			}
			curNivo.pop_back();
		}
		tmpNivoji.pop();
	}
	return seznamPoti;
}

int main()
{
	int steviloVozlisc;
	int cena;
	int** sosedi = nullptr;

	bool nadaljuj = true;
	int izbira;
	string path;

	ifstream f;

	auto start = std::chrono::steady_clock::now();;
	auto end = std::chrono::steady_clock::now();;

	stack<list<pot>> nivoji; 
	stack<list<pot>> tmpNivoji;
	list<pot> nivo;

	vector<pot> seznamPoti;

	do
	{
		printMeni();
		cin >> izbira;
		switch (izbira)
		{
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

			//Vnos v matrike sosedov
			for (int i = 0; i < steviloVozlisc; i++)
			{
				for (int j = 0; j < steviloVozlisc; j++)
				{
					f >> cena;
					sosedi[i][j] = cena;
				}
			}
			//----------------

			f.close();
			break;
		case 2:
			start = std::chrono::steady_clock::now();;
			nivoji = potnik(sosedi, steviloVozlisc);
			end = std::chrono::steady_clock::now();;

			cout << "Cas iskanja najkrajse poti: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << "microsec." << std::endl;
			cout << "Cena: " << nivoji.top().back().cena << endl << endl;
			break;
		case 3:
			tmpNivoji = nivoji;
			while (!tmpNivoji.empty()) {
				nivo = tmpNivoji.top();
				cout << "Stevilo poti na nivoju: " << nivo.size() << endl;
				while (!nivo.empty()) {
					pot pot = nivo.back();
					cout << "Iz: " << pot.iz_vozlisca + 1 << ", v: " << pot.v_vozlisce + 1 << ", cena: " << pot.cena << ", mnozica: ";
					for (int j = 0; j < pot.mnozica.size(); j++) cout << pot.mnozica[j] << " ";
					cout << endl;
					nivo.pop_back();
				}
				tmpNivoji.pop();
			}
			break;
		case 4:
			seznamPoti = rekonstrukcijaPoti(nivoji);
			for (int i = 0; i < seznamPoti.size(); i++) {
				std::cout << seznamPoti[i].iz_vozlisca + 1 << " ";
			}
			cout << seznamPoti[seznamPoti.size() - 1].v_vozlisce + 1 << endl;
			break;
		case 5:
			nadaljuj = false;
			break;
		default:
			break;
		}
	} while (nadaljuj);
}