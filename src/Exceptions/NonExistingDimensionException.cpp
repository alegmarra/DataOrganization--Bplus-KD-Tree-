#include "NonExistingDimensionException.h"
#include <sstream>

NonExistingDimensionException::NonExistingDimensionException(
    int dim, unsigned _size) : exception() {
    dimension = dim;
    size = _size;
}

const char* NonExistingDimensionException::what() const throw() {
    std::ostringstream oss;
    oss << "Asked for dimension " << dimension
        << ". Dimension ought to be in range [0; " << size << ")";
    return oss.str().c_str();
}



