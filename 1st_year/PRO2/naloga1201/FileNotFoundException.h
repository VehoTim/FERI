//
// Created by tim on 13. 06. 2021.
//

#ifndef NALOGA1201_FILENOTFOUNDEXCEPTION_H
#define NALOGA1201_FILENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

class FileNotFoundException : public std::exception {
private:
    std::string message;
public:
    FileNotFoundException(std::string path);
    const char * what() const noexcept override;
};


#endif //NALOGA1201_FILENOTFOUNDEXCEPTION_H
