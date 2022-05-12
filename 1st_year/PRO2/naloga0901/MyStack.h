//
// Created by tim on 19. 05. 2021.
//

#ifndef NALOGA0901_MYSTACK_H
#define NALOGA0901_MYSTACK_H

#include <vector>
#include <sstream>
#include "Date.h"

template <typename T>
class MyStack {
private:
    std::vector<T> values;
    std::string name;
public:
    MyStack(std::string &name1) :name(name1) {}

    bool empty(){ return values.empty(); }

    int size() { return values.size(); }

    T top(){ return values.back(); }

    void push(T element){ values.push_back(element); }

    bool pop(){
        if(this->empty()) return false;
        values.pop_back();
        return true;
    }

    std::string toString(){
        std::stringstream ss;
        for (int i = values.size() - 1; i >= 0 ; --i) {
            ss << values[i] << std::endl;
        }
        return ss.str();
    }

    void popX(int X){
        for (int i = 0; i < X; ++i) {
            this->pop();
        }
    }

    std::vector<T> backX(int X){
        std::vector<T> tmp;
        for (int i = 0; i < X; ++i) {
            tmp.push_back(values[i]);
        }
        return tmp;
    }

    void pushX(std::vector<T> vec){
        for (int i = 0; i < vec.size(); ++i) {
            this->push(vec[i]);
        }
    }

    void reverse(){
        std::vector<T> tmp;
        for (int i = values.size() - 1; i >= 0; --i) {
            tmp.push_back(values[i]);
        }
        this->values = tmp;
    }

    void removeEven(){
        int size = values.size();
        for (int i = 0; i < size; i+=2) {
            values.erase(values.begin() + i);
        }
    }

    std::vector<T> topX(int X){
        std::vector<T> tmp;
        for (int i = values.size() - 1; i > (values.size() - 1 - X); --i) {
            tmp.push_back(values[i]);
        }
        return tmp;
    }
};

template<>
std::string MyStack<Date>::toString() {
    std::stringstream ss;
    for (int i = values.size() - 1; i >= 0 ; --i) {
        ss << values[i].toString() << std::endl;
    }
    return ss.str();
}

#endif //NALOGA0901_MYSTACK_H
