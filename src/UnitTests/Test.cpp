#ifndef TEST_CPP_
#define TEST_CPP_

#include <iostream>
#include <assert.h>

class Test{
public:
	virtual void run()= 0;
	virtual ~Test(){}
};
#endif /* TEST_CPP_ */
