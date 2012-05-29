#include "Test.cpp"

#include "../KDTree/Query/Condition.h"
#include "../KDTree/Query.h"
#include "../KDTree/RecordID/IntKey.h"

#include "../KDTree/RecordID/Infinity.h"


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
            
            QueryCondition * c;
            
            try {
                c = new QueryCondition(new IntKey(1, 2), new IntKey(10, 2));
                delete c;
                pass();
            } catch (...) {
                fail("Invalid range in range constructor");
            }
            
            
            try {
                c = new QueryCondition(new IntKey(10, 2), new IntKey(1, 2));
                fail("Range constructor accepted an invalid range");
                delete c;            
            } catch (...) {
                pass();
            }
            
            stop();
        }
        
        void test_SetHi() 
        {
            start("SetHi");

            QueryCondition * c;
            
            c = new QueryCondition(new IntKey(10, 2));

            try {
                c->setHi(new IntKey(15, 2));
                pass();
            } catch (...) {
                fail("Could not change Hi Key to a valid value");
            }

            delete c;

            // =================================================================

            c = new QueryCondition(new IntKey(10, 2));

            try {
                c->setHi(new KeyInfinity(true));
                pass();
            } catch (...) {
                fail("Could not change Hi Key to +Infinity");
            }

            delete c;

            // =================================================================

            c = new QueryCondition(new IntKey(10, 2));

            try {
                c->setHi(new IntKey(5, 2));
                fail("Allowed an invalid value for Hi Key");
            } catch (...) {
                pass();
            }

            delete c;

            stop();
        }
        
        void test_SetLow() 
        {
            start("SetLow");

            QueryCondition * c;
            
            c = new QueryCondition(new IntKey(10, 2));

            try {
                c->setLow(new IntKey(5, 2));
                pass();
            } catch (...) {
                fail("Could not change Low Key to a valid value");
            }

            delete c;

            c = new QueryCondition(new IntKey(10, 2));

            try {
                c->setLow(new IntKey(15, 2));
                fail("Allowed an invalid value for Low Key");
            } catch (...) {
                pass();
            }

            delete c;
            
            stop();
        }
        
        void test_InRange() 
        {
            start("InRange");
            
            QueryCondition c = QueryCondition(new IntKey(10, 2), new IntKey(20, 2));
            IntKey k1(5, 2);
            IntKey k2(15, 2);
            IntKey k3(25, 2);
            
            if (c.inRange(&k1)) fail("5 is not in range [10,20]");
            else pass();
            
            if (c.inRange(&k2)) pass();
            else fail("15 is in range [10,20]");
            
            if (c.inRange(&k3)) fail("25 is not in range [10,20]");
            else pass();
            
            stop();
        }
        
        void test_Eval()
        {
            start("Eval");

            IntKey k1(5, 2);
            IntKey k2(15, 2);
            IntKey k3(25, 2);
            
            QueryCondition * c;
            
            c = new QueryCondition();

            if (c->eval(&k1) == Query::MATCH) pass();
            else {
                switch (c->eval(&k1))
                {
                    case Query::LOWER:
                    fail("Any key should match an infinite range condition. Got LOWER"); 
                    break;
                    
                    case Query::HIGHER:
                    fail("Any key should match an infinite range condition. Got HIGHER"); 
                    break;
                    
                    case Query::EQUAL:
                    fail("Any key should match an infinite range condition. Got EQUAL"); 
                    break;
                
                    default:        
                    fail("Any key should match an infinite range condition"); 
                    break;
                }
            }
            delete c;
            
            c = new QueryCondition(new IntKey(15, 2));
            
            if (c->eval(&k1) == Query::LOWER) pass();
            else fail("5 is LOWER than 15"); 

            if (c->eval(&k2) == Query::EQUAL) pass();
            else fail("15 is EQUAL to 15");
            
            if (c->eval(&k3) == Query::HIGHER) pass();
            else fail("25 is HIGHER than 15");
                                    
            delete c;
            
            c = new QueryCondition(new IntKey(10, 2), new IntKey(20, 2));

            if (c->eval(&k1) == Query::LOWER) pass();
            else fail("5 is below range [10,20]"); 

            if (c->eval(&k2) == Query::MATCH) pass();
            else fail("15 is contained in range [10,20]");
            
            if (c->eval(&k3) == Query::HIGHER) pass();
            else fail("25 is above range [10,20]");

            delete c;

            stop();
        }
};
