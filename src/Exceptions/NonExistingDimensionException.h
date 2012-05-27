#ifndef NON_EXISTING_DIMENSION_EXCEPTION_H
#define NON_EXISTING_DIMENSION_EXCEPTION_H

#include <exception>

class NonExistingDimensionException: public std::exception {
    public:
        NonExistingDimensionException(int dim, unsigned _size);
        virtual const char* what() const throw();
    private:
        unsigned size;
        int dimension;
};

#endif  // NON_EXISTING_DIMENSION_EXCEPTION_H
