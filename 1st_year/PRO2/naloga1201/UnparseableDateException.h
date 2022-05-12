//
// Created by tim on 12. 06. 2021.
//

#ifndef NALOGA1201_UNPARSEABLEDATEEXCEPTION_H
#define NALOGA1201_UNPARSEABLEDATEEXCEPTION_H

#include <exception>
#include <string>

class UnparseableDateException : public std::exception {
private:
    std::string message;
public:
    UnparseableDateException(std::string datum);
    const char * what() const noexcept override;
};


#endif //NALOGA1201_UNPARSEABLEDATEEXCEPTION_H
