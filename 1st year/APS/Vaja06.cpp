#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>

void printMeni() {
	std::cout << "Hitro uredi - izbira\n\n";
	std::cout << "1) Generiraj nakljucno zaporedje\n";
	std::cout << "2) Generiraj narascajoce zaporedje\n";
	std::cout << "3) Generiraj padajoce zaporedje\n";
	std::cout << "4) Izpis zaporedja\n";
	std::cout << "5) Preveri ali je zaporedje urejeno\n";
	std::cout << "6) Uredi s hitrim urejanjem brez mediane\n";
	std::cout << "7) Uredi s hitrim urejanjem z mediano\n";
	std::cout << "8) Uredi z drugim algoritmom za urejanjem\n";
	std::cout << "9) Konec\n\n";
	std::cout << "Izbira: ";
}

void fill(std::vector<double> &vector, int N) {
	srand(time(nullptr));
	for (int i = 0; i < N; i++) 
	{
		vector.push_back(rand());
	}
}

void fillSorted(std::vector<double> &vector, int N) {
	srand(time(nullptr));
	for (int i = 0; i < N; i++)
	{
		vector.push_back(i);
	}
}

void fillSorted2(std::vector<double> &vector, int N) {
	srand(time(nullptr));
	int j = N - 1;
	for (int i = 0; i < N; i++)
	{
		vector.push_back(j);
		j--;
	}
}

int deli(std::vector<double> &vector, int &dno, int &vrh) {
	int pe = vector[dno];
	int l = dno;
	int d = vrh;

	while (l < d)
	{
		while (vector[l] <= pe && l < vrh) l++;
		while (vector[d] >= pe && d > dno) d--;

		if (l < d) std::swap(vector[l], vector[d]);
	}
	std::swap(vector[dno], vector[d]);
	return d;
}

int deliM(std::vector<double> &vector, int &dno, int &vrh) {
	int mediana = dno + (vrh - dno) / 2;
	std::swap(vector[dno], vector[mediana]);
	int pe = vector[dno];
	int l = dno;
	int d = vrh;

	while (l < d)
	{
		while (vector[l] <= pe && l < vrh) l++;
		while (vector[d] >= pe && d > dno) d--;

		if (l < d) std::swap(vector[l], vector[d]);	
	}
	std::swap(vector[dno], vector[d]);
	return d;
}

void quickSort(std::vector<double> &vector, int dno, int vrh) {
	//double x[10000]; x[0] = 0;
	if (dno < vrh)
	{	
		int j = deli(vector, dno, vrh);
		quickSort(vector, dno, j - 1);
		quickSort(vector, j + 1, vrh);
	}
}

void quickSortM(std::vector<double> &vector, int dno, int vrh) {
	//double x[10000]; x[0] = 0;
	if (dno < vrh)
	{
		int j = deliM(vector, dno, vrh);
		quickSortM(vector, dno, j - 1);
		quickSortM(vector, j + 1, vrh);
	}
}


bool preveriZaporedje(std::vector<double> &vector, int N) {
	for (int i = 0; i < vector.size() - 1; i++)
	{
		if (vector[i] > vector[i + 1]) return false;
	}
	return true;
}

void urejanjeZMehurcki(std::vector<double> &vector, int N) {
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (vector[j] > vector[j + 1]) std::swap(vector[j], vector[j + 1]);
		}
	}
}

int main()
{
	int izbira;
	int dolzina;
	std::vector<double> vector;

	auto start = std::chrono::steady_clock::now();;
	auto end = std::chrono::steady_clock::now();;

	do
	{
		printMeni();
		std::cin >> izbira;

		switch (izbira)
		{
		case 1:
			vector.clear();
			std::cout << "Izberi dolzino zaporedja: ";
			std::cin >> dolzina;
			fill(vector, dolzina);
			break; 
		case 2:
			vector.clear();
			std::cout << "Izberi dolzino zaporedja: ";
			std::cin >> dolzina;
			fillSorted(vector, dolzina);
			break;
		case 3:
			vector.clear();
			std::cout << "Izberi dolzino zaporedja: ";
			std::cin >> dolzina;
			fillSorted2(vector, dolzina);
			break;
		case 4:
			for (int i = 0; i < dolzina; i++) std::cout << vector[i] << " ";
			std::cout << std::endl;
			break;
		case 5:
			if (preveriZaporedje(vector, dolzina)) std::cout << "Zaporedje je urejeno" << std::endl;
			else std::cout << "Zaporedje ni urejeno" << std::endl;
			std::cout << vector.size() << std::endl;
			break;
		case 6:
			start = std::chrono::steady_clock::now();
			quickSort(vector, 0, dolzina - 1);
			std::cout << "Urejanje koncano\n";
			end = std::chrono::steady_clock::now();
			std::cout << "Cas trajanja urejenja: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"microsec." << std::endl;
			break;
		case 7:
			start = std::chrono::steady_clock::now();
			quickSortM(vector, 0, dolzina - 1);
			std::cout << "Urejanje z mediano koncano\n";
			end = std::chrono::steady_clock::now();
			std::cout << "Cas trajanja urejenja: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"microsec." << std::endl;
			break;
		case 8:
			start = std::chrono::steady_clock::now();
			urejanjeZMehurcki(vector, dolzina);
			std::cout << "Urejanje z mehurcki koncano\n";
			end = std::chrono::steady_clock::now();
			std::cout << "Cas trajanja urejenja: " << std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count() <<
				"microsec." << std::endl;
			break;
		case 9:
			return 0;
			break;
		default:
			break;
		}

	} while (true);
}
