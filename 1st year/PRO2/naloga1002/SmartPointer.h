//
// Created by tim on 24. 05. 2021.
//

#ifndef NALOGA1001_SMARTPOINTER_H
#define NALOGA1001_SMARTPOINTER_H

#include "ReferenceCounter.h"

template<typename T>
class SmartPointer {
private:
    T *pData;
    ReferenceCounter *counter;
    static int NoOfEqualExpresions;
public:
    SmartPointer(T *data) : pData(data) {
        counter = new ReferenceCounter();
        (*counter)++;
    }

    SmartPointer(SmartPointer<T> &smartPointer) {
        this->pData = smartPointer.pData;
        this->counter = smartPointer.counter;
    }

    ~SmartPointer() {
        if (useCount() <= 0) {
            delete pData;
            pData = nullptr;
            return;
        }
        --(*counter);
    }

    T &operator*() {
        return *pData;
    }

    T *operator->() {
        return pData;
    }

    SmartPointer &operator=(const SmartPointer &other) {
        if (this->pData != other.pData) {
            --(*counter);
            if (counter->getCount() == 0) {
                delete pData;
                delete counter;
            }
            this->pData = other.pData;
            this->counter = other.counter;
            (*counter)++;
        } else NoOfEqualExpresions++;
        return *this;
    }

    int useCount() {
        return counter->getCount();
    }

    int getNoOfEqualExpresion() {
        return NoOfEqualExpresions;
    }

    // ...
};

template<typename T>
int SmartPointer<T>::NoOfEqualExpresions = 0;

#endif //NALOGA1001_SMARTPOINTER_H
