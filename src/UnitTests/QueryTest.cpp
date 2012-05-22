#ifndef QUERY_TEST_CPP
#define QUERY_TEST_CPP

#include <assert.h>
#include <iostream>
#include "KDTree/Query.h"
#include "KDTree/Key.h"
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
        
        q->addCondition(new QueryCondition())
            ->addCondition(new QueryCondition())
            ->addCondition(new QueryCondition());
        
        assert(q->size() == 3);

        std::cout << "test_addCondition: OK"
				  << std::endl;
        
        delete q;
    
    }
    
    void test_evalIntKey_NoError()
    {
        Query* q;
        Key* k1 = new Key(4);
        Key* k2 = new Key(14);
        Key* k3 = new Key(30);

        // k <= 10
        // .:. -Inf < k <= 10
        /*
        q = new Query;
        q->addCondition(new QueryCondition(new KeyInfinity(), new Key(10)));
        
        assert(q->eval(k1));        
        assert(!q->eval(k2));
        assert(!q->eval(k3));
      
        delete q;
        */
        // k >= 5
        // .:. 5 <= k < +Inf
        q = new Query();
        q->addCondition(new QueryCondition(new Key(5), new KeyInfinity(true)));
        
        assert(!q->eval(k1));        
        assert(q->eval(k2));
        assert(q->eval(k3));
      
        delete q;
        
        // 10 <= k <= 20
        q = new Query();
        q->addCondition(new QueryCondition(new Key(10), new Key(20)));
        
        assert(!q->eval(k1));        
        assert(q->eval(k2));
        assert(!q->eval(k3));
      
        delete q;
    }
    
};

#endif
