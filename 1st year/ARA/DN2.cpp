#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

ofstream out;

string inputText(const string& pot) {
	ifstream input(pot);
	stringstream sstream;

	if (!input.is_open()) {
		return string();
	}

	sstream << input.rdbuf();
	return sstream.str();
}

void izpis_BCH(vector<unsigned int> polje) {
	for (int i = 0; i < polje.size(); ++i) {
		out << polje[i] << ' ';
	}
	out << endl;
}

void Sunday(const string& text, const string& vzorec) {
	vector<unsigned int> BCH(256, vzorec.length() + 1);

	for (int i = 0; i < vzorec.length(); i++) BCH[vzorec[i]] = vzorec.length() - i;

	izpis_BCH(BCH);

	vector<int> index;
	int j = 0;

	for (int i = 0; i < vzorec.length(); i++)
	{
		if ((text.length() - vzorec.length()) < j) break;

		if (vzorec[i] != text[j + i]) {
			i = 0;
			j += BCH[text[j + vzorec.length() - i]];
		}

		if (i == vzorec.length() - 1) {
			i = 0;
			index.push_back(j);
			j += vzorec.length();
		}
	}

	for (int i : index) {
		out << i << " ";
	}
}

int main(int argc, const char* const argv[]) {
	if (argc != 3) {
		return -1;
	}

	string text = inputText(argv[2]);
	string vzorec = argv[1];
	out.open("out.txt");

	if (!out) {
		return -2;
	}

	Sunday(text, vzorec);
	return 0;
}