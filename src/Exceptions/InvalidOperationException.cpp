#include <exception>

class InvalidOperationException: public std::exception
{
private:
	const char * message;
public:

	InvalidOperationException(const char * msj){
		message = msj;
	}

	virtual const char* what() const throw()
  {
    return message;
  }

};
