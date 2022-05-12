//
// Created by timve on 26. 05. 2021.
//

#include "ReferenceCounter.h"

ReferenceCounter::ReferenceCounter() {
}

ReferenceCounter &ReferenceCounter::operator--() {
    this->count -= 1;
    return *this;
}

ReferenceCounter ReferenceCounter::operator++(int dummy) {
    count += 1;
    return *this;
}

int ReferenceCounter::getCount() const {
    return count;
}

void ReferenceCounter::setCount(int c) {
    this->count = c;
}
