#include "Test.cpp"

class ConditionTest: public Test 
{
public:
    ConditionTest(): Test("Condition") { }
    
    virtual void run() 
    {
        test_EmptyConstructor();
        test_OneKeyConstructor();
        test_RangeConstructor();
        test_setHi();
        test_setLow();
    }
    
private:

        void test_EmptyConstructor() 
        {
            start("EmptyConstructor");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_OneKeyConstructor() 
        {
            start("OneKeyConstructor");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_RangeConstructor() 
        {
            start("RangeConstructor");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_setHi() 
        {
            start("setHi");
            fail("Not implemented yet!");
            stop();
        }
        
        void test_setLow() 
        {
            start("setLow");
            fail("Not implemented yet!");
            stop();
        }
};
