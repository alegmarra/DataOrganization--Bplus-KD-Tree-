#include <exception>

class InvalidTargetException: public std::exception
{
public:
  virtual const char* what() const throw()
  {
    return "Invalid target for Comparison";
  }

};
