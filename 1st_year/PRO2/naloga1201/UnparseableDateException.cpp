//
// Created by tim on 12. 06. 2021.
//

#include "UnparseableDateException.h"
#include <sstream>


UnparseableDateException::UnparseableDateException(std::string datum){
    std::stringstream ss;
    ss << "Unparseable date: \"" << datum << "\"";
    message = ss.str();
}

const char *UnparseableDateException::what() const noexcept {
    return message.c_str();
}
