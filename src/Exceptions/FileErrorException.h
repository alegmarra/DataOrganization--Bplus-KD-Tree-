#ifndef FILE_ERROR_EXCEPTION_H
#define FILE_ERROR_EXCEPTION_H

#include <exception>

class FileErrorException: public std::exception {
    public:
        FileErrorException(const char* msg, int nodeNumber);
        virtual const char* what() const throw();
    private:
        int nodeNumber;
        char extraInfo[40];
};

#endif  // FILE_ERROR_EXCEPTION_H
