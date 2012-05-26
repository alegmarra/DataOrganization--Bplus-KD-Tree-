#include "InvalidIntSizeException.h"
#include <sstream>

InvalidIntSizeException::InvalidIntSizeException(int _size) : exception() {
    size = _size;
}

const char* InvalidIntSizeException::what() const throw() {
    std::ostringstream oss;
    oss << "Initializing integer type with size " << size;
    return oss.str().c_str();
}


