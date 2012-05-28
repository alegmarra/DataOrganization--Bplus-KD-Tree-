#ifndef QUERY_TEST_CPP
#define QUERY_TEST_CPP

#include <stdio.h>
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
        
        q->addCondition(1, new QueryCondition())
            ->addCondition(1, new QueryCondition())
            ->addCondition(2, new QueryCondition());
        
        if (q->size() == 3) pass();
        else {
            char buff[50];
            sprintf(buff, "Expected query size 3. Got %d.", q->size());
            fail(buff);
        }

        
        delete q;
        stop();
    }
    
    /**
     * @todo Mejorar este test porque ahora es como los de Condition
     */
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
        q->addCondition(1, new QueryCondition(new KeyInfinity(), new IntKey(10, 2)));
        
        if(q->eval(1, k1) == Query::MATCH) pass();
        else fail("4 out of range [-inf,10]");
        
        if(q->eval(1, k2) == Query::HIGHER) pass();
        else fail("14 in range [-inf,10]");
        
        if(q->eval(1, k3) == Query::HIGHER) pass();
        else fail("30 in range [-inf,10]");
      
        delete q;
        
        // k >= 5
        // .:. 5 <= k < +Inf
        q = new Query();
        q->addCondition(1, new QueryCondition(new IntKey(5, 2), new KeyInfinity(true)));
        
        if(q->eval(1, k1) == Query::LOWER) pass();
        else fail("4 in range [5,+inf]");
                
        if(q->eval(1, k2) == Query::MATCH) pass();
        else fail("14 out of range [5,+inf]");
        
        if(q->eval(1, k3) == Query::MATCH) pass();
        else fail("30 out of range [5,+inf]");
      
        delete q;
        
        // 10 <= k <= 20
        q = new Query();
        q->addCondition(1, new QueryCondition(new IntKey(10, 2), new IntKey(20, 2)));
        
        if(q->eval(1, k1) == Query::LOWER) pass();
        else fail("4 in range [10,20]");
        
        if(q->eval(1, k2) == Query::MATCH) pass();
        else fail("14 out of range [10,20]");
        
        if(q->eval(1, k3) == Query::HIGHER) pass();
        else fail("30 out of range [10,20]");
      
        delete q;

        // 14 == k == 14
        q = new Query();
        q->addCondition(1, new QueryCondition(new IntKey(14, 2), new IntKey(14, 2)));
        
        if(q->eval(1, k1) == Query::LOWER) pass();
        else fail("4 is not equal to 14");
        
        if(q->eval(1, k2) == Query::EQUAL) pass();
        else fail("14 should be equal to 14");
        
        if(q->eval(1, k3) == Query::HIGHER) pass();
        else fail("30 is not equal to 14");
      
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
