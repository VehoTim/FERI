#include "Text.h"

Text::Text(vector<string> lines) : lines(lines){
}

int Text::returnVowels() const{
    int count = 0;
    for (string line : lines){
        for (int i = 0; i < line.length(); ++i) {
            if (tolower(line[i]) == 'a' || tolower(line[i]) == 'e' ||
                tolower(line[i]) == 'i' || tolower(line[i]) == 'o' ||
                tolower(line[i]) == 'u') count++;
        }
    }
    return count;
}

int Text::returnConsonants() const{
    int count = 0;
    for (string line : lines){
        for (int i = 0; i < line.length(); ++i) {
            if (tolower(line[i]) == 'a' || tolower(line[i]) == 'e' ||
                tolower(line[i]) == 'i' || tolower(line[i]) == 'o' ||
                tolower(line[i]) == 'u');
            else count++;
        }
    }
    return count;
}

bool Text::isIn(string str) const{
    bool found = 0;
    for (string line : lines){
        found = line.find(str) != string::npos;
        if(found) return found;
    }
    return found;
}

string Text::toString() const{
    string str;
    for(string line : lines){
        str+=line;
        str+=" ";
    }
    return str;
}

bool Text::isInt(const string &str) {
    int num = str.length();
    for (char c : str) {
        if (isdigit(c)) num--;
    }
    if (num == 0) return true;
    else return false;
}

int Text::stringToInt(const std::string &str) {
    if (isInt(str)) return stoi(str);
    else return INT32_MIN;
}

bool Text::isValidEmail(const std::string &email) {
    bool found = false;
    for (int i = 0; i < email.length(); ++i) {
        if (email[i] == '@') found = true;
        if (found && email[i] == '.') return true;
    }
    return false;
}

string Text::backwards(const string &str){
    string b;
    b.resize(str.length());
    int j = 0;
    for (int i = str.length() - 1; i >= 0 ; --i) {
        b[j] = str[i];
        j++;
    }
    return b;
}

void Text::fixSlovenianSZ(string &str) {
    if (tolower(str[0]) == 's' && (str[1] == ' ' || str[1] == '\n')){
        char c3 = tolower(str[2]);
        if (c3 ==  'c' || c3 == 's' || c3 == 'f' || c3 == 'h' || c3 == 'k' || c3 == 'p' || c3 == 't');
        else {
            if (str[0] == 's') str[0] = 'z';
            else str[0] = 'Z';
        }
    }
    else if(tolower(str[0]) == 'z' && (str[1] == ' ' || str[1] == '\n')){
        char c3 = tolower(str[2]);
        if (c3 ==  'c' || c3 == 's' || c3 == 'f' || c3 == 'h' || c3 == 'k' || c3 == 'p' || c3 == 't'){
            if (str[0] == 'z') str[0] = 's';
            else str[0] = 'S';
        }
    }
    for (int i = 1; i < str.length(); ++i) {
        if (str[i] == '.' || str[i] == ',' || str[i] == ';'  || str[i] == ' '  || str[i] == '\n'){
            if ((tolower(str[i+1]) == 's') && (str[i+2] == ' ' || str[i+2] == '\n')){
                char c3 = tolower(str[i+3]);
                if (c3 ==  'c' || c3 == 's' || c3 == 'f' || c3 == 'h' || c3 == 'k' || c3 == 'p' || c3 == 't');
                else {
                    if (str[i+1] == 's') str[i+1] = 'z';
                    else str[i+1] = 'Z';
                }
            }
            else if((tolower(str[i+1]) == 'z')&& (str[i+2] == ' ' || str[i+2] == '\n')){
                char c3 = tolower(str[i+3]);
                if (c3 ==  'c' || c3 == 's' || c3 == 'f' || c3 == 'h' || c3 == 'k' || c3 == 'p' || c3 == 't'){
                    if (str[i+1] == 'z') str[i+1] = 's';
                    else str[i+1] = 'S';
                }
            }
        }
    }

}
