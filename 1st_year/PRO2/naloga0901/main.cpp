#include <iostream>
#include "MyStack.h"
#include "Point.h"

/*Ustvarite razredno šablono Point, ki kot argument prejme tip T.
Razred naj ima dve instančni spremenljivki tipa T, x in y.
Implementirajte naslednje metode:
Point &move(T, T);
bool equal(const Point &) const;
std::string to_string() const;
Specializirate šablono za tip float, tako da bo metoda equal vrnila true če sta vrednosti približno enaki.
Uporabite lahko kar:
abs(x - y) < 0.0000001;
OPOZORILO: Ta pristop ne deluje pravilno v robnih primerih, za več informaciji poglejte naslednji link:
https://stackoverflow.com/questions/4915462/how-should-i-do-floating-point-comparison*/




int main() {
    std::string name = "doubles";
    MyStack<double> doubles(name);

    name = "strings";
    MyStack<std::string> strings(name);

    name = "dates";
    MyStack<Date> dates(name);

    std::cout << "DOUBLE:" << std::endl;
    if (doubles.empty()) std::cout << "Stack is empty\n";
    else std::cout << "Stack is not empty\n";

    doubles.push(2.7);

    doubles.pushX(std::vector<double>{4, 6.2, 6.6, 1.23, 3.6});

    std::cout << doubles.toString() << std::endl;

    if (doubles.pop()) std::cout << "Pop successful\n";
    else std::cout << "Pop unsuccessful\n";

    std::cout << doubles.toString() << std::endl;

    std::cout << "STRING:" << std::endl;
    strings.pushX(std::vector<std::string>{"str", "another", "more", "yet", "pop", "stock"});

    std::cout << "Size: " << strings.size() << endl;

    std::cout << "Top: " << strings.top() << endl;

    strings.popX(3);

    std::cout << strings.toString() << std::endl;

    std::cout << "DATE:" << std::endl;

    dates.pushX(std::vector<Date>{Date(17, 2, 2001), Date(22, 3, 2012),
                                  Date(28, 4, 2015), Date(15, 6, 2019),
                                  Date(30, 12, 1980)});

    dates.reverse();

    std::cout << dates.toString() << std::endl;

    vector<Date> topDates = dates.topX(2);

    std::cout << "Dates on top: " << std::endl;
    for(Date d : topDates){
        std::cout << d.toString() << std::endl;
    }

    dates.removeEven();

    std::cout << "After removing even:\n" << dates.toString() << std::endl;

    vector<Date> botDates = dates.backX(2);

    std::cout << "Dates on the back: " << std::endl;
    for(Date d : botDates){
        std::cout << d.toString() << std::endl;
    }


    cout << endl;
    Point<float> a(3.04, 1.03);
    a = a.move(1.01, 2.003);
    cout << a.equal(Point<float>(4.05, 3.033)) << endl;
    cout << a.to_string() << endl;

    Point<int> b(3, 1);
    b = b.move(1, 3);
    cout << b.equal(Point<int>(4, 3)) << endl;
    cout << b.to_string() << endl;

    return 0;
}
