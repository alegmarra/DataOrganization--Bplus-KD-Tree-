#ifndef TEST_CPP_
#define TEST_CPP_

#include <iostream>
#include <assert.h>

#define TESTING 1
#define BLOCKSIZE 4096
#define K   5

class Test{
public:
	virtual void run()= 0;
	virtual ~Test(){}
};
#endif /* TEST_CPP_ */
