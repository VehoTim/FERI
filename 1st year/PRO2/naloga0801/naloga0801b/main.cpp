#include <iostream>
#include "Date.h"
#include "Time.h"
#include "Person.h"
#include <vector>

template<typename T>
//Any type
T largest(T t1, T t2, T t3) {
    if ((t1 >= t2) && (t1 >= t3)) return t1;
    else if ((t2 >= t1) && (t2 >= t3)) return t2;
    else return t3;
}

//string
template<>
std::string largest<std::string>(std::string t1, std::string t2, std::string t3) {
    if (t1.length() >= t2.length() && t1.length() >= t3.length()) return t1;
    else if (t2.length() >= t1.length() && t2.length() >= t3.length()) return t2;
    else return t3;
}

//date (first from previous classes)
template<>
Date largest<Date>(Date t1, Date t2, Date t3) {
    if (((t1.getYear() > t2.getYear()) || (t1.getYear() == t2.getYear() && t1.getMonth() > t2.getMonth()) ||
         (t1.getYear() == t2.getYear() && t1.getMonth() == t2.getMonth() && t1.getDay() > t2.getDay()))
        && ((t1.getYear() > t3.getYear()) || (t1.getYear() == t3.getYear() && t1.getMonth() > t3.getMonth()) ||
            (t1.getYear() == t3.getYear() && t1.getMonth() == t3.getMonth() && t1.getDay() > t3.getDay())))
        return t1;
    else if (((t2.getYear() > t1.getYear()) || (t2.getYear() == t1.getYear() && t2.getMonth() > t1.getMonth()) ||
              (t2.getYear() == t1.getYear() && t2.getMonth() == t1.getMonth() && t2.getDay() > t1.getDay()))
             && ((t2.getYear() > t3.getYear()) || (t2.getYear() == t3.getYear() && t2.getMonth() > t3.getMonth()) ||
                 (t2.getYear() == t3.getYear() && t2.getMonth() == t3.getMonth() && t2.getDay() > t3.getDay())))
        return t2;
    else return t3;
}

//time (second from previous classes)
template<>
Time largest<Time>(Time t1, Time t2, Time t3) {
    if (((t1.getHour() > t2.getHour()) || (t1.getHour() == t2.getHour() && t1.getMinute() > t2.getMinute()) ||
         (t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute() && t1.getSecond() > t2.getSecond()))
        && ((t1.getHour() > t3.getHour()) || (t1.getHour() == t3.getHour() && t1.getMinute() > t3.getMinute()) ||
            (t1.getHour() == t3.getHour() && t1.getMinute() == t3.getMinute() && t1.getSecond() > t3.getSecond())))
        return t1;
    else if (((t2.getHour() > t1.getHour()) || (t2.getHour() == t1.getHour() && t2.getMinute() > t1.getMinute()) ||
              (t2.getHour() == t1.getHour() && t2.getMinute() == t1.getMinute() && t2.getSecond() > t1.getSecond()))
             && ((t2.getHour() > t3.getHour()) || (t2.getHour() == t3.getHour() && t2.getMinute() > t3.getMinute()) ||
                 (t2.getHour() == t3.getHour() && t2.getMinute() == t3.getMinute() && t2.getSecond() > t3.getSecond())))
        return t2;
    else return t3;
}

//custom class
template<>
Person largest<Person>(Person t1, Person t2, Person t3) {
    if ((t1.getHeight() >= t2.getHeight()) && (t1.getHeight() >= t3.getHeight())) return t1;
    else if ((t2.getHeight() >= t1.getHeight()) && (t2.getHeight() >= t3.getHeight())) return t2;
    else return t3;
}

template<typename X>
std::vector<X> toVector2X(X a, X b, int n){
    vector<X> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(a);
        vec.push_back(b);
    }
    return vec;
}

template<typename S>
double sizeOfVector(vector<S> vec){
    return sizeof(S) * vec.size();
}

int main() {
    double a = 1., b = 2., c = 3.;
    cout << "The largest number between " << a << " and " << b << " and " << c << " is " << largest(a, b, c) << "."
         << endl;

    std::string s1 = "Srednje dolg", s2 = "Drugi niz bo najdaljsi niz", s3 = "Kratek";
    cout << largest<std::string>(s1, s2, s3) << endl;

    Date d1(10, 3, 2012), d2(10, 2, 2012), d3(7, 3, 2012);
    cout << largest<Date>(d1, d2, d3).toString() << endl;

    Time t1(10, 30, 0), t2(10, 20, 15), t3(12, 03, 02);
    cout << largest<Time>(t1, t2, t3).toString() << endl;

    Person p1("Tim", "Vehovar", 176, 62), p2("Manjsa", "Oseba", 160, 70), p3("Vecja", "Oseba", 182, 55);
    cout << largest<Person>(p1, p2, p3).toString();

    //------------------------------------------------------

    vector<Person> people = toVector2X(p1, p2, 4);
    cout << "\nVelikost: " << sizeOfVector(people) << "B" << endl;
    for(Person p : people) cout << p.toString() << endl;

    vector<int> integers = toVector2X(3, 6, 3);
    cout << "\nVelikost: " << sizeOfVector(integers) << "B" << endl;
    for(int i : integers) cout << i << endl;

    vector<char> characters = toVector2X('i', '@', 2);
    cout << "\nVelikost: " << sizeOfVector(characters) << "B" << endl;
    for(int c : characters) cout << (char)c << endl;
}
