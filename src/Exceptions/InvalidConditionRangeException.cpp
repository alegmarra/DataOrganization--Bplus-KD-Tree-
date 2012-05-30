#include "InvalidConditionRangeException.h"

const char* InvalidConditionRangeException::what() const throw() {
    return "Low Key should be lower than or equal to Hi Key";
}

