#ifndef NALOGA0501_BOARD_H
#define NALOGA0501_BOARD_H

/*
name: std::string,
tasks: std::vector<Task*> (seznam vseh nalog; kompozicija),
konstruktor (z enim parametrom, ime table),
void addTask(Task* task),
std::string toString() const.
 */

#include <string>
#include <vector>
#include "Task.h"
#include <map>

/*
Razredu Board dodajte instančno spremenljivko std::map<std::string, std::vector<Task *>> byTag in metodo:
std::vector<Task *> findTaskByTag(const std::string &);
Metoda naj vrne kazalec na instance razreda Task, ki imajo podan tag.*/


using namespace std;

class Board {
private:
    string name;
    std::map<std::string, Task*> tasks;

    std::map<std::string, std::vector<Task *>> byTag;
public:
    Board(string name);
    bool addTask(Task* task);
    string toString() const;
    Task* findTask(const std::string &key) const;
    void deleteTask(const std::string &key);
    unsigned int numberOfTasks() const;
    static std::vector<Task*> toVector(Board board);

    void clearTasks();
    void swapTasks(const string &key1, const string &key2);
    void changeDate(const string &key, DateTime newDT);

    std::vector<Task *> findTaskByTag(const std::string &);
};


#endif //NALOGA0501_BOARD_H
