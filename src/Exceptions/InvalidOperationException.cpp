#include <exception>

class InvalidOperationException: public std::exception
{
public:
  virtual const char* what() const throw()
  {
    return "Wrong File Type";
  }

};
