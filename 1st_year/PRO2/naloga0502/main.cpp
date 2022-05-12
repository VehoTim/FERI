#include <iostream>
#include "Board.h"
#include "ExpirationTask.h"

int main() {
    Board* tabla = new Board("Nova tabla");

    DateTime datum1(Date(31,3,2021), Time(17,17,0));
    DateTime datum2(Date(27,3,2021), Time(10,20,0));
    DateTime datum3(Date(31,3,2021), Time(1,30,0));
    DateTime datum4(Date(30,5,2010), Time(12,24,0));
    DateTime datum5(Date(7,12,2020), Time(15,46,0));

    DateTime deadline1(Date(17,4,2021), Time(1,30,0));
    DateTime deadline2(Date(30,6,2010), Time(12,24,0));
    DateTime deadline3(Date(25,12,2021), Time(15,46,0));

    Category c1("Kategorija1");
    Category c2("Kategorija2");
    Category c3("Kategorija3");

    tabla->addCategory(c1);
    tabla->addCategory(c2);
    tabla->addCategory(c3);

    Task* t1 = new Task("Task1", "opis taska je tukaj", datum1);
    Task* t2 = new Task("Task2", "opis taska je tukaj", datum2);
    ExpirationTask* et1 = new ExpirationTask("Task3", "opis taska je tukaj", datum3, "Tim", deadline1, "DOING");
    ExpirationTask* et2 = new ExpirationTask("Task4", "opis taska je tukaj", datum4, "Vehovar", deadline2, "DONE");
    ExpirationTask* et3 = new ExpirationTask("Task2", "opis taska je tukaj", datum5, "Assignee", deadline3, "TODO");

    tabla->addTask("Kategorija1", t1);
    tabla->addTask("Kategorija3", t2);
    tabla->addTask("Kategorija3", et1);
    tabla->addTask("Kategorija", et2);
    tabla->addTask("Kategorija3", et3);

    cout << tabla->toString() << endl;

    Board nova = tabla->removeAllWithTaskName("Task2");

    cout << nova.toString() << endl;

    cout << "Assigni 31.3.2021: \n";
    tabla->agenda(Date(31,3,2021));

    if(et1->isExpired(DateTime(Date(1,4,2021), Time(17,30,0)))){
        cout << endl << "Task is expired!" << endl;
    }

    if (tabla->changeName("Kategorija1", "Category1")) cout << tabla->toString();

    delete tabla;

    return 0;
}
