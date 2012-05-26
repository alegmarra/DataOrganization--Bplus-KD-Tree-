#ifndef FILE_NOT_SET_EXCEPTION_H
#define FILE_NOT_SET_EXCEPTION_H

#include <exception>

class FileNotSetException: public std::exception {
    public:
      virtual const char* what() const throw();

};

#endif  // FILE_NOT_SET_EXCEPTION_H

