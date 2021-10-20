//
// Created by timve on 26. 05. 2021.
//

#ifndef NALOGA1002_REFERENCECOUNTER_H
#define NALOGA1002_REFERENCECOUNTER_H


class ReferenceCounter {
private:
    int count = 0;
public:
    ReferenceCounter();
    ReferenceCounter& operator--();
    ReferenceCounter operator++(int dummy);

    int getCount() const;
    void setCount(int c);
};


#endif //NALOGA1002_REFERENCECOUNTER_H
