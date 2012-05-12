#include <exception>

class InvalidKeyException: public std::exception
{
public:
  virtual const char* what() const throw()
  {
    return "Invalid value for a Key";
  }

};
