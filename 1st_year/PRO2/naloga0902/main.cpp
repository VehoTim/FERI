#include <iostream>
#include "Board.h"
#include "ExpirationTask.h"

//tasku vector tagov
//map z vectorjem taskom v boardu
int main() {
    Board tabla("Nova tabla");

    DateTime datum1(Date(31,3,2021), Time(17,17,0));
    DateTime datum2(Date(27,3,2021), Time(10,20,0));
    DateTime datum3(Date(17,2,2019), Time(1,30,0));
    DateTime datum4(Date(30,5,2010), Time(12,24,0));
    DateTime datum5(Date(7,12,2020), Time(15,46,0));

    DateTime deadline1(Date(17,4,2021), Time(1,30,0));
    DateTime deadline2(Date(30,6,2010), Time(12,24,0));
    DateTime deadline3(Date(25,12,2021), Time(15,46,0));

    Task* t1 = new Task("Task1", "opis taska je tukaj", datum1);
    Task* t2 = new Task("Task1", "opis taska je tukaj", datum2);
    ExpirationTask* et1 = new ExpirationTask("ExpirationTask1", "opis taska je tukaj", datum3, "Tim", deadline1, "DOING");
    ExpirationTask* et2 = new ExpirationTask("ExpirationTask2", "opis taska je tukaj", datum4, "Vehovar", deadline2, "DONE");
    ExpirationTask* et3 = new ExpirationTask("ExpirationTask3", "opis taska je tukaj", datum5, "Assignee", deadline3, "TODO");

    t1->addTag("navaden");
    t2->addTag("navaden");
    t1->addTag("kul");
    et1->addTag("poseben");
    et3->addTag("navaden");

    if(tabla.addTask(t1)) cout << "Successfully added\n";
    else cout << "Task with this name already exists\n";
    if(tabla.addTask(t2)) cout << "Successfully added\n";
    else cout << "Task with this name already exists\n";
    if(tabla.addTask(et1)) cout << "Successfully added\n";
    else cout << "Task with this name already exists\n";
    if(tabla.addTask(et2)) cout << "Successfully added\n";
    else cout << "Task with this name already exists\n";
    if(tabla.addTask(et3)) cout << "Successfully added\n";
    else cout << "Task with this name already exists\n";

    vector<Task *> navadni = tabla.findTaskByTag("navaden");

    for(Task* t : navadni){
        cout << t->toString() << endl;
    }

    cout << tabla.toString();

    /*if(tabla.findTask("ExpirationTask2") != nullptr)
        cout << tabla.findTask("ExpirationTask2")->toString() << endl;

    tabla.deleteTask("ExpirationTask2");

    if(tabla.findTask("ExpirationTask2") != nullptr)
        cout << tabla.findTask("ExpirationTask2")->toString() << endl;

    cout << "Number of tasks: " << tabla.numberOfTasks() << endl;

    vector<Task *> vec = Board::toVector(tabla);
    cout << endl;
    for(Task* t: vec){
        cout << t->toString() << endl;
    }

    tabla.swapTasks("ExpirationTask3","ExpirationTask1");

    tabla.changeDate("Task1", DateTime(Date(17,2,2001), Time(12, 30 ,0)));

    cout << tabla.toString();*/

    tabla.clearTasks();
    delete t2;
    t2 = nullptr;

    return 0;
}
