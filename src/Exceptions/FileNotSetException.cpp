#include "FileNotSetException.h"

const char* FileNotSetException::what() const throw() {
    return "Trying to serialize/deserialize with no file";
}

