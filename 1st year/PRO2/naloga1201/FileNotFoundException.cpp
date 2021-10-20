//
// Created by tim on 13. 06. 2021.
//

#include "FileNotFoundException.h"
#include <sstream>

FileNotFoundException::FileNotFoundException(std::string path){
    std::stringstream ss;
    ss << "Can't find path: \"" << path << "\"";
    message = ss.str();
}

const char *FileNotFoundException::what() const noexcept {
    return message.c_str();
}
