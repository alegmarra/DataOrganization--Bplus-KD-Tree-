#include <exception>

class InvalidKeyException: public std::exception
{
private:
	const char * eMessage;
public:

	InvalidKeyException(const char * message){
		eMessage = message;
	}

	virtual const char* what() const throw()
  {
    return eMessage;
  }

};
