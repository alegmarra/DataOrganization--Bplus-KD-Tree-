#ifndef TEST_CPP_
#define TEST_CPP_

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#define TESTING 1
#define BLOCKSIZE 4096
#define K   5

class Test 
{

private:

    std::string name;
    std::vector<std::string> errors;    
    bool failed;

public:
    Test(std::string test_name)
    {
        name = test_name;
        
        std::cout << std::endl << name << "Test BEGIN: " << std::endl << std::endl;

    }
    
    void start(std::string subtest)
    {
		std::cout << "test_" << subtest << ": ";
        failed = false;
    }
    
    void pass()
    {
        std::cout << ".";
    }
    
    void fail(std::string error)
    {
        failed = true;
        std::cout << "F";
        errors.push_back(error);
    }
    
    void stop()
    {
        if (failed) {
            std::cout << " Test Failed!";
        } else {
            std::cout << " OK";
        }
        
        failed = false;
        std::cout << std::endl;
    }
    
	virtual void run()= 0;

	virtual ~Test() {
	    if (errors.size() > 0) {
	    
	        std::cout << std::endl << "Errors found:" << std::endl << std::endl;
	        
	        for (unsigned i = 0; i< errors.size(); i++) {
	            std::cout << "  *  " << errors[i] << std::endl;
	        }
	        
	        std::cout << std::endl;
	    }
	
	    std::cout << "-------" << name << "Test END-------" << std::endl;
	    
        assert(errors.size() == 0);
	}
};
#endif /* TEST_CPP_ */
