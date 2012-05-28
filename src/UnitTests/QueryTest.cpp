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
        start("addCondition_NoError");
        
        Query* q = new Query;
        
        q->addCondition(new QueryCondition())
            ->addCondition(new QueryCondition())
            ->addCondition(new QueryCondition());
        
        if (q->size() == 3) pass();
        else fail("Expected query size 3");

        
        delete q;
        stop();
    }
    
    void test_evalIntKey_NoError()
    {
        start("evalIntKey_NoError");
        
        Query* q;
        Key* k1 = new IntKey(4, 2);
        Key* k2 = new IntKey(14, 2);
        Key* k3 = new IntKey(30, 2);

        // k <= 10
        // .:. -Inf < k <= 10
        q = new Query;
        q->addCondition(new QueryCondition(new KeyInfinity(), new IntKey(10, 2)));
        
        if(q->eval(k1)) pass();
        else fail("4 out of range [-inf,10]");
        
        if(!q->eval(k2)) pass();
        else fail("14 in range [-inf,10]");
        
        if(!q->eval(k3))pass();
        else fail("30 in range [-inf,10]");
      
        delete q;
        
        // k >= 5
        // .:. 5 <= k < +Inf
        q = new Query();
        q->addCondition(new QueryCondition(new IntKey(5, 2), new KeyInfinity(true)));
        
        if(!q->eval(k1)) pass();
        else fail("4 in range [5,+inf]");
                
        if(q->eval(k2)) pass();
        else fail("14 out of range [5,+inf]");
        
        if(q->eval(k3)) pass();
        else fail("30 out of range [5,+inf]");
      
        delete q;
        
        // 10 <= k <= 20
        q = new Query();
        q->addCondition(new QueryCondition(new IntKey(10, 2), new IntKey(20, 2)));
        
        if(!q->eval(k1)) pass();
        else fail("4 in range [10,20]");
        
        if(q->eval(k2)) pass();
        else fail("14 out of range [10,20]");
        
        if(!q->eval(k3)) pass();
        else fail("30 out of range [10,20]");
      
        delete q;
        
        stop();
    }
    
    virtual void run()
    {

        test_addCondition_NoError();
        test_evalIntKey_NoError();

	}
};

#endif
