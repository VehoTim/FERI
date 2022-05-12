#include <iostream>

using namespace std;

int main()
{
	//Vpis hitrosti
	cout << "Vpisi hitrost: ";
	double hitrost;
	cin >> hitrost;

	//Vpis trajanja
	cout << "\nVpisi trajanje: ";
	double traj;
	cin >> traj;

	//Vpis dolzine poti
	cout << "\nVpisi dolžino proge: ";
	double dol;
	cin >> dol;

	//Izpis vseh podatkov
	cout << endl << hitrost << " " << traj << " " << dol << endl;

	//Izracun mankajoce poti
	double man_pot = dol - traj * hitrost;

	//Izpis mankajoce poti in racuna
	cout << "\nMankajoca pot (" << man_pot << ") = dolzina poti (" << dol << ") - trajanje (" << traj << ") * hitrost (" << hitrost << ")" << endl;

	//IF stavek
	if (man_pot < 0)
	{
		cout << "\nKolesar je ze mimo cilja.";
	}
	else cout << "\nKolesar se ima " << man_pot << "km";
}
