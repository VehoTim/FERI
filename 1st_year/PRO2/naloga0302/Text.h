#ifndef NALOGA0302_TEXT_H
#define NALOGA0302_TEXT_H

#include <iostream>
#include <vector>

using namespace std;


class Text {
private:
    vector<string> lines;
public:
    Text(vector<string> lines);

    int returnVowels() const;

    int returnConsonants() const;

    bool isIn(string str) const;

    string toString() const;

    static bool isInt(const string &str);

    static int stringToInt(const string &str);

    static bool isValidEmail(const string &email);

    static string backwards(const string &str);

    static void fixSlovenianSZ(string &str);
};


#endif //NALOGA0302_TEXT_H
