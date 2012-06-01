#include "FileErrorException.h"
#include <sstream>
#include <cstring>

FileErrorException::FileErrorException(const char* msg, int _nodeNumber) :
    exception() {
    nodeNumber = _nodeNumber;
    strcpy(extraInfo, msg);
}

const char* FileErrorException::what() const throw() {
    std::ostringstream oss;
    oss << "Something went wrong with the file (asked for block number "
        << nodeNumber << " while " << extraInfo << ")";
    return oss.str().c_str();
}


