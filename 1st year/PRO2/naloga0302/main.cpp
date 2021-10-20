#include <iostream>
#include <vector>
#include "Text.h"

using namespace std;

/*1. Napiši metodo fixSlovenianSZ(), ki v tekstu preveri vse pojavitve s in z in jih ustrezno po potrebi
    popravi (male in velike črke).
Npr: Z sankami grem. -> S sankami grem.
    ...smo.Z sanami grem.-> ...smo.S sankami grem.



redlog S se uporablja pred soglasniki – c, č, f, h, k, p, s, š, t drugače Z.*/

int main() {
    vector<string> lines;
    lines.push_back("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor");
    lines.push_back("incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud");
    lines.push_back("exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure");
    Text txt(lines);

    cout << "Number of vowels: " << txt.returnVowels() << endl;
    cout << "Number of consonants: " << txt.returnConsonants() << endl;

    if(txt.isIn("ea")) cout << "yes\n";
    else cout << "no\n";

    cout << txt.toString() << endl;

    if(Text::isInt("236343")) cout << "number\n";
    else cout << "not number\n";

    int num = Text::stringToInt("235543");
    cout << (num + 2);

    if (Text::isValidEmail("notvalid.@.")) cout << "\nvalid email\n";
    else cout << "\nnot valid email\n";

    cout << Text::backwards("tim");

    string test = "Z sankami grem, z korenom";

    Text::fixSlovenianSZ(test);

    cout << endl << test;

    return 0;
}
