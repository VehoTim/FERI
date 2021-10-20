#include <iostream>
#include "Date.h"
#include "SmartPointer.h"
#include <memory>
#include "Animal.h"

int main() {
    Date* date1 = new Date(27, 2, 2001);
    {
        SmartPointer<Date> sp1(date1);
        cout << sp1->toString() << endl;
        cout << ++(*sp1) << endl;
        (*sp1)++;
        cout << (*sp1) << endl;
    }
    //cout << sp1->toString();
    cout << date1->toString() << endl;

    SmartPointer<Date> sp2(new Date(30, 4, 2020));
    SmartPointer<Date> sp3(new Date(30, 4, 2020));
    if(*sp3 == *sp2) cout << sp3->toString() << endl;
    (*sp3)++;
    cout << sp3->toString() << endl;

    cout << "Shared pointers: \n";
    Date* date2 = new Date(29,4,2030);
    {
        shared_ptr<Date> sharedPtr1(date2);
        cout << sharedPtr1->toString() << endl;
        (*sharedPtr1)++;
        ++(*sharedPtr1);
        cout << (*sharedPtr1) << endl;
    }
    cout << date2->toString() << endl;

    shared_ptr<Date> sharedPtr2(new Date(30, 12, 2020));
    shared_ptr<Date> sharedPtr3(new Date(31, 12, 2020));
    if(*sharedPtr3 == *sharedPtr2) cout << sharedPtr3->toString() << endl;
    (*sharedPtr3)++;
    cout << sharedPtr3->toString() << endl;

    SmartPointer<Animal> spA1(new Animal(32.0));
    cout << (*spA1)++ << endl;
    cout << ++(*spA1) << endl;

    return 0;
}
