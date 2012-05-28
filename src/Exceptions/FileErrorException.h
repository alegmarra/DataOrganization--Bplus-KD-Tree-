#ifndef FILE_ERROR_EXCEPTION_H
#define FILE_ERROR_EXCEPTION_H

#include <exception>

class FileErrorException: public std::exception {
    public:
      virtual const char* what() const throw();
};

#endif  // FILE_ERROR_EXCEPTION_H
