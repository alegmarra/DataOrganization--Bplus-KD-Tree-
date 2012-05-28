#ifndef INVALID_INT_SIZE_EXCEPTION_H
#define INVALID_INT_SIZE_EXCEPTION_H

#include <exception>

class InvalidIntSizeException: public std::exception {
    public:
        InvalidIntSizeException(int _size);
        virtual const char* what() const throw();
    private:
        int size;
};

#endif  // INVALID_INT_SIZE_EXCEPTION_H
