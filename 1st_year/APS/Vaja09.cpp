#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

struct povezava {
	povezava(int p, int q, int cena) {
		this->p = p;
		this->q = q;
		this->cena = cena;
	}

	string toString() {
		stringstream ss;
		ss << p << " " << q << " " << cena;
		return ss.str();
	}

	int p;
	int q;
	int cena;
};

void printMeni() {
	cout << "Kruskalov algoritem - izbira:\n" << endl;
	cout << "1) Preberi graf iz datoteke\n";
	cout << "2) Generiraj nakljucni graf\n";
	cout << "3) Pozeni\n";
	cout << "4) Izpis sprejetih povezav\n";
	cout << "5) Konec\n" << endl;
	cout << "Izbira: ";
}

int deli(vector<povezava>& vec, int& dno, int& vrh) {
	int pe = vec[dno].cena;
	int l = dno;
	int d = vrh;

	while (l < d)
	{
		while (vec[l].cena <= pe && l < vrh) l++;
		while (vec[d].cena >= pe && d > dno) d--;

		if (l < d) swap(vec[l], vec[d]);
	}
	swap(vec[dno], vec[d]);
	return d;
}

void hitroUredi(vector<povezava>& vec, int dno, int vrh)
{
	if (dno < vrh) {
		int j = deli(vec, dno, vrh);
		hitroUredi(vec, dno, j - 1);
		hitroUredi(vec, j + 1, vrh);
	}
}

vector<povezava> kruskal(vector<povezava> P, int n) {
	hitroUredi(P, 0, P.size() - 1);
	//vector<povezava> R;
	vector<vector<povezava>> mnozice{};

	int najdena = 2; // 0 - pripadata isti; 1 - pripadata razlicnim; 2 - se ne obstaja
	bool iskanje1;
	bool iskanje2;
	int i;
	int indexBrisi;
	vector<povezava> temp;
	for (povezava& e : P)
	{
		iskanje1 = false;
		iskanje2 = false;
		najdena = 2;
		//for (vector<povezava> mn : mnozice) {
		for (i = 0; i < mnozice.size(); i++) {
			for (povezava& m : mnozice[i]) {
				if ((m.p == e.p || m.q == e.p)) iskanje1 = true;
				if (m.p == e.q || m.q == e.q) iskanje2 = true;

				if (iskanje1 && iskanje2 && najdena == 2) {
					najdena = 0;
					break;
				}
				else if (iskanje1 && iskanje2 && najdena == 1) {
					break;
				}
			}
			if (najdena == 0) break;
			else if (najdena == 1) {
				break;
			}
			else if (iskanje1 || iskanje2) {
				najdena = 1;
				indexBrisi = i;
				temp = mnozice[i];
				continue;
			}
		}

		if (najdena == 2) {
			mnozice.push_back(vector<povezava>{e});
		}
		else if (najdena == 1) {
			if (iskanje1 && iskanje2) {
				for (povezava& x : temp) mnozice[i].push_back(x);
				mnozice[i].push_back(e);
				mnozice.erase(mnozice.begin() + indexBrisi);
			}
			else if (iskanje1 || iskanje2) {
				mnozice[indexBrisi].push_back(e);
			}
		}
	}

	if (mnozice[0].size() == n - 1) return mnozice[0];
	else return vector<povezava>{};
}

int main()
{
	int steviloVozlisc, steviloPovezav = 0;
	int indeksV1, indeksV2, cena;
	vector<povezava> povezave;

	string preberiIzbiro;
	bool nadaljuj = true;
	int izbira;
	string path;

	//case 2
	vector<int> uporabljena;
	int v1, v2;
	bool n1, n2;

	auto start = std::chrono::steady_clock::now();;
	auto end = std::chrono::steady_clock::now();;

	ifstream f;

	while (nadaljuj) {
		printMeni();
		cin >> izbira;
		switch (izbira)
		{
		case 1:
			cout << "Vpisi ime datoteke: ";
			cin >> path;
			f.open(path);

			f >> steviloVozlisc;
			f >> steviloPovezav;

			povezave.clear();
			for (int i = 0; i < steviloPovezav; i++)
			{
				f >> indeksV1 >> indeksV2 >> cena;
				povezave.push_back(povezava(indeksV1, indeksV2, cena));
			}
			f.close();
			break;
		case 2:
			povezave.clear();
			uporabljena.clear();
			steviloPovezav = 0;
			do {
				cout << "Vpisi stevilo vozlisc (do 1500): ";
				cin >> steviloVozlisc;
			} while (steviloVozlisc > 1500 || steviloVozlisc < 0);
			srand(time(nullptr));
			for (int i = 0; (i < steviloVozlisc) /*|| kruskal(povezave, steviloVozlisc).size() == 0*/;) //komentirano == hitreje ampak ni vedno povezan graf
			{
				n1 = n2 = false;
				do {
					v1 = rand() % steviloVozlisc + 1;
					v2 = rand() % steviloVozlisc + 1;
				} while (v1 == v2);
				for (povezava& p : povezave) if (p.p == v2 && p.q == v1) continue;	//neusmerjen graf
				povezave.push_back(povezava(v1, v2, rand() % 20 + 1));
				steviloPovezav += 1;
				for (int n : uporabljena) {
					if (v1 == n) {
						n1 = true;
					}
					if (v2 == n) {
						n2 = true;
					}
				}
				if (!n1) {
					uporabljena.push_back(v1);
					i++;
				}
				if (!n2) {
					uporabljena.push_back(v2);
					i++;
				}
			}
			break;
		case 3:
			start = std::chrono::steady_clock::now();;
			povezave = kruskal(povezave, steviloVozlisc);
			end = std::chrono::steady_clock::now();;
			cout << "Stevilo vozlisc: " << steviloVozlisc << endl;
			cout << "Stevilo povezav na zacetku: " << steviloPovezav << endl;
			cout << "Stevilo sprejetih povezav: " << povezave.size() << endl;
			cout << "Iskanje je trajalo: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << "microsec." << std::endl;
			break;
		case 4:
			if (povezave.size() == 0) {
				cout << "Graf ni povezan!\n";
			}
			else {
				cout << "p q cena" << endl;
				for (povezava p : povezave) {
					cout << p.toString() << endl;
				}
			}
			break;
		case 5:
			nadaljuj = false;
			break;
		default:
			break;
		}
	}
}
