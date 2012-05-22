#ifndef QUERY_TEST_CPP
#define QUERY_TEST_CPP

#include <assert.h>
#include <iostream>
#include "KDTree/Query.h"
#include "KDTree/Query/Condition.h"

class QueryTest 
{

public:
  
	QueryTest()
	{
		std::cout << "QueryTest BEGIN: "
				  << std::endl 
				  << std::endl;
	}
  
    void test_addCondition_NoError() 
    {
    
        Query* q = new Query;
        
        q->addCondition(new Condition())
            ->addCondition(new Condition())
            ->addCondition(new Condition());
        
        assert(q->size() == 3);

        std::cout << "test_addCondition: OK"
				  << std::endl;
        
        delete q;
    
    }
    
};

#endif
