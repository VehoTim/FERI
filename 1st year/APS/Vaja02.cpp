#include <iostream>

using namespace std;

struct Sklad {
	int* sk;
	int vrh = 0;
	int MAX;

	//Push a new number on Top of stack
	void Push(int x) {
		if (vrh == MAX) cout << "Napaka: polno\n";
		else {
			sk[vrh] = x;
			vrh++;
		}
	}

	//Pop last number from stack
	void Pop() {
		if (vrh == 0) cout << "Napaka: prazno\n";
		else {
			vrh--;
			//cout << sk[vrh] << endl;
		}
	}

	//Print all numbers from stack
	void Print() {
		if (vrh == 0)
			cout << "/";
		else
		{
			for (int i = 0; i < vrh; i++)
			{
				cout << sk[i] << " ";
			}
		}
		cout << endl;
	}

	//Return last number from stack
	int Top() {
		return sk[vrh-1];
	}

	bool Empty() {
		return (vrh == 0);
	}
};

Sklad a;
Sklad b;
Sklad c;

void Move(Sklad& y, Sklad& z) {
	if (z.Top() > y.Top() || z.Empty())
	{
		z.Push(y.Top());
		y.Pop();
	}
	else cout << "Vecjega ne smes dati na manjsega!\n";
}

void printAll() {
	cout << "\nStolp 1: ";
	a.Print();
	cout << "\nStolp 2: ";
	b.Print();
	cout << "\nStolp 3: ";
	c.Print();
}

int main()
{

	cout << "Vpisi velikost stolpa: ";
	int x;
	cin >> x;

	a.MAX = x;
	a.sk = new int[x];
	b.MAX = x;
	b.sk = new int[x];
	c.MAX = x;
	c.sk = new int[x];
	//Napolnimo sklad (stolp a)
	for (int i = x; i > 0; i--)
	{
		a.Push(i);
	}



	int y;
	int z;
	do
	{
		printAll();

		cout << "\nIz katerega stolpa zelis premakniti? (1/2/3) ";
		cin >> y;

		switch (y)
		{
			case 1:
				if (!(a.Empty()))
				{
					do
					{
						cout << "\nNa kateri stolp zelis premakniti? (2/3) ";
						cin >> z;
						if (z == 2)
						{
							Move(a, b);
							break;
						}
						else if (z == 3)
						{
							Move(a, c);
							break;
						}
						else {
							cout << "Vpisan je napacen stolp";
						}

					} while (true);
					
				}
				else {
					cout << "\nTa stolp je prazen\n";
					continue;
				}
				break;
			case 2:
				if (!(b.Empty()))
				{
					do
					{
						cout << "\nNa kateri stolp zelis premakniti? (1/3) ";
						cin >> z;
						if (z == 1)
						{
							Move(b, a);
							break;
						}
						else if (z == 3)
						{
							Move(b, c);
							break;
						}
						else {
							cout << "Vpisan je napacen stolp";
						}

					} while (true);

				}
				else {
					cout << "\nTa stolp je prazen\n";
					continue;
				}
				break;
			case 3:
				if (!(c.Empty()))
				{
					do
					{
						cout << "\nNa kateri stolp zelis premakniti? (1/2) ";
						cin >> z;
						if (z == 1)
						{
							Move(c, a);
							break;
						}
						else if (z == 2)
						{
							Move(c, b);
							break;
						}
						else {
							cout << "Vpisan je napacen stolp";
						}

					} while (true);

				}
				else {
					cout << "\nTa stolp je prazen\n";
					continue;
				}
				break;
			default:
				cout << "Vnesen stolp ne obstaja!\n";
				continue;
				break;
		}

		if (x == b.vrh || x == c.vrh)
		{
			cout << "\nCestitam uspesno si prestavil stolp\n";
			break;
		}
	} while (true);

	printAll();
}
