#ifndef QUERY_TEST_CPP
#define QUERY_TEST_CPP

#include <assert.h>
#include <iostream>
#include "Test.cpp"

#include "../KDTree/Query.h"
#include "../KDTree/RecordID/IntKey.h"
#include "../KDTree/RecordID/Infinity.h"
#include "../KDTree/Query/Condition.h"

class QueryTest: public Test
{

public:
  
	QueryTest(): Test("Query") { }
  
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
        Key* k1 = new IntKey(4, 2);
        Key* k2 = new IntKey(14, 2);
        Key* k3 = new IntKey(30, 2);

        // k <= 10
        // .:. -Inf < k <= 10
        q = new Query;
        q->addCondition(new QueryCondition(new KeyInfinity(), new IntKey(10, 2)));
        
        assert(q->eval(k1));        
        assert(!q->eval(k2));
        assert(!q->eval(k3));
      
        delete q;
        
        // k >= 5
        // .:. 5 <= k < +Inf
        q = new Query();
        q->addCondition(new QueryCondition(new IntKey(5, 2), new KeyInfinity(true)));
        
        assert(!q->eval(k1));        
        assert(q->eval(k2));
        assert(q->eval(k3));
      
        delete q;
        
        // 10 <= k <= 20
        q = new Query();
        q->addCondition(new QueryCondition(new IntKey(10, 2), new IntKey(20, 2)));
        
        assert(!q->eval(k1));        
        assert(q->eval(k2));
        assert(!q->eval(k3));
      
        delete q;
        
        std::cout << "test_evalIntKey: OK"
				  << std::endl;
        
    }
    
    virtual void run()
    {

        test_addCondition_NoError();
        test_evalIntKey_NoError();

	}
};

#endif
