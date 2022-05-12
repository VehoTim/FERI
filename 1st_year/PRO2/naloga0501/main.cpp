#include <iostream>
#include "Board.h"
#include "ExpirationTask.h"

//V glavnem programu ustvarite eno tablo in ji dodajte vsaj pet nalog (nekaj z rokom in nekaj brez). Ne pozabite na brisanje objektov in uporabo že vsega do sedaj pridobljenega znanja.

int main() {
    Board* tabla = new Board("Nova tabla");

    DateTime datum1(Date(31,3,2021), Time(17,17,0));
    DateTime datum2(Date(27,3,2021), Time(10,20,0));
    DateTime datum3(Date(17,2,2019), Time(1,30,0));
    DateTime datum4(Date(30,5,2010), Time(12,24,0));
    DateTime datum5(Date(7,12,2020), Time(15,46,0));

    DateTime deadline1(Date(17,4,2021), Time(1,30,0));
    DateTime deadline2(Date(30,6,2010), Time(12,24,0));
    DateTime deadline3(Date(25,12,2021), Time(15,46,0));

    Task* t1 = new Task("Task1", "opis taska je tukaj", datum1);
    Task* t2 = new Task("Task2", "opis taska je tukaj", datum2);
    ExpirationTask* et1 = new ExpirationTask("Task3", "opis taska je tukaj", datum3, "Tim", deadline1, "DOING");
    ExpirationTask* et2 = new ExpirationTask("Task4", "opis taska je tukaj", datum4, "Vehovar", deadline2, "DONE");
    ExpirationTask* et3 = new ExpirationTask("Task5", "opis taska je tukaj", datum5, "Assignee", deadline3, "TODO");
    tabla->addTask(t1);
    tabla->addTask(t2);
    tabla->addTask(et1);
    tabla->addTask(et2);
    tabla->addTask(et3);

    cout << tabla->toString();
    cout << endl << tabla->exportJSON();

    delete tabla;

    cout << tabla->toString();
    return 0;
}
