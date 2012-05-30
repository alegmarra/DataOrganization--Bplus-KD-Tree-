#ifndef INVALID_CONDITION_RANGE_EXCEPTION_H
#define INVALID_CONDITION_RANGE_EXCEPTION_H

#include <exception>

class InvalidConditionRangeException: public std::exception {
    public:
      virtual const char* what() const throw();

};

#endif 
