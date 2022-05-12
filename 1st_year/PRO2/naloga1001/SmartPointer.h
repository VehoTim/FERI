//
// Created by tim on 24. 05. 2021.
//

#ifndef NALOGA1001_SMARTPOINTER_H
#define NALOGA1001_SMARTPOINTER_H

template<typename T>
class SmartPointer {
private:
    T* pData;

public:
    SmartPointer(T* data) : pData(data) {}
    ~SmartPointer(){
        delete pData;
        pData = nullptr;
    }

    T& operator*() {
        return *pData;
    }
    T* operator->() {
        return pData;
    }

    // ...
};


#endif //NALOGA1001_SMARTPOINTER_H
