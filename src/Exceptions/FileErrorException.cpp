#include "FileErrorException.h"

const char* FileErrorException::what() const throw() {
    return "Something went wrong with the file";
}


