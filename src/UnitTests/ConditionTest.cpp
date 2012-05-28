#include "Test.cpp"

#include "../KDTree/Query/Condition.h"
#include "../KDTree/RecordID/IntKey.h"


class ConditionTest: public Test 
{
public:
    ConditionTest(): Test("Condition") { }
    
    virtual void run() 
    {
        test_EmptyConstructor();
        test_OneKeyConstructor();
        test_RangeConstructor();
        test_SetHi();
        test_SetLow();
        test_InRange();
        test_Eval();
    }
    
private:

        /**
         * Dummy test
         */
        void test_EmptyConstructor() 
        {
            start("EmptyConstructor");
            
            QueryCondition * c = new QueryCondition();
            delete c;
            
            pass();
            
            stop();
        }
        
        /**
         * Dummy test
         */
        void test_OneKeyConstructor() 
        {
            start("OneKeyConstructor");
            
            QueryCondition * c = new QueryCondition(new IntKey(10, 2));
            delete c;
           
            pass();            
            
            stop();
        }
        
        void test_RangeConstructor() 
        {
            start("RangeConstructor");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_SetHi() 
        {
            start("SetHi");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_SetLow() 
        {
            start("SetLow");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_InRange() 
        {
            start("InRange");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_Eval()
        {
            start("Eval");
            fail("Not implemented yet!");
            stop();
        }
};
