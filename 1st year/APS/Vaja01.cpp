#include <iostream>

using namespace std;

struct Sklad {
	int* sk;
	int vrh;
	int MAX;

	//Push a new number on top of stack
	void Push(int* sk, int x) {
		if (vrh == MAX) cout << "Napaka: polno\n";
		else {
			sk[vrh] = x;
			vrh++;
		}
	}

	//Pop last number from stack
	void Pop(int* sk) {
		if (vrh == 0) cout << "Napaka: prazno\n";
		else {
			vrh--;
			cout << sk[vrh] << endl;
		}
	}
	
	//Print all numbers from stack
	void Print(int* sk) {
		if (vrh==0)
			cout << "Vrsta je prazna\n";
		else
		{
			for (int i = 0; i < vrh; i++)
			{
				cout << sk[i] << " ";
			}
		}
		cout << endl;
	}
};

struct Vrsta {
	int* kv;
	int glava;
	int rep;
	int MAX;

	void Push(int* kv, int x) {
		int novi_rep = rep + 1;
		if (novi_rep >= MAX)  novi_rep = 0;
		
		if (glava == novi_rep) cout << "Napaka: polno\n";
		else
		{
			kv[rep] = x;
			rep = novi_rep;
		}
	}

	void Pop(int* kv) {
		if (glava == rep)	cout << "Napaka: prazno\n";
		else {
			int x = kv[glava];
			glava++;
			if (glava >= MAX) glava = 0;

			cout << x << endl;
		}
	}

	void Print(int* kv) {
		if (rep == glava)
			cout << "Vrsta je prazna\n";
		else
		{
			//if glava is 0, print from start to rep
			if (glava == 0)	
			{
				for (int i = glava; i < rep; i++)
				{
					cout << kv[i] << " ";
				}
			}
			else
			{
				//if rep before glava
				if (rep <= glava)
				{
					//first print from glava to MAX
					for (int i = glava; i < MAX; i++)
					{
						cout << kv[i] << " ";
					}
					//then those numbers before glava in circle
					for (int i = 0; i < rep; i++)
					{
						cout << kv[i] << " ";
					}
				}
				//else print from glava to rep
				else {
					for (int i = glava; i < rep; i++)
					{
						cout << kv[i] << " ";
					}
				}
			}
		}
		cout << endl;
	}
};


int main()
{
	Sklad S;
	Vrsta V;

	//input max size
	cout << "Vpisi velikosti vrste in sklada: ";
	int max;
	cin >> max;

	//set values of variables in stack
	S.MAX = max;
	S.sk = new int[max];
	S.vrh = 0;

	//set values of variables in circular array
	V.MAX = max;
	V.kv = new int[max];
	V.glava = 0;
	V.rep = 0;

	//loop for menu
	int izb = 0;
	do
	{
		cout << "\nSklad - izbira:\n";
		cout << "1. Vnos podatka\n";
		cout << "2. Branje podatka in izpis\n";
		cout << "3. Izpis vsebine sklada\n";
		cout << "\nKrozna vrsta - izbira:\n";
		cout << "4. Vnos podatka\n";
		cout << "5. Branje podatka in izpis\n";
		cout << "6. Izpis vrste od glave do repa\n";
		cout << "\n7. Konec\n\n";

		cin >> izb;
		int x;

		//switch case for calling certain functions
		switch (izb)
		{
		case 1:
			cout << "Katero stevilo zelis dodati: ";
			cin >> x;
			S.Push(S.sk, x);
			break;
		case 2:
			S.Pop(S.sk);
			break;
		case 3:
			S.Print(S.sk);
			break;
		case 4:
			cout << "Katero stevilo zelis dodati: ";
			cin >> x;
			V.Push(V.kv, x);
			break;
		case 5:
			V.Pop(V.kv);
			break;
		case 6:
			V.Print(V.kv);
			break;
		default:
			cout << "Poskusi drugo stevilo";
			break;
		}
	} while (izb!=7);

	delete []S.sk;
	delete []V.kv;
	S.sk = nullptr;
	V.kv = nullptr;
}
