#include "UnitTests/KeyTest.cpp"
#include "UnitTests/QueryTest.cpp"


int main() 
{

	KeyTest * key_test = new KeyTest();

	key_test->test_StringConstructor_NoError();
	key_test->test_StringConstructor_Throws_InvalidKeyException();
	key_test->test_NumberConstructor_NoError();
	key_test->test_NumberConstructor_Throws_InvalidKeyException();
	key_test->test_getKey_NoError();
	key_test->test_KeyComparator_NoError();
    key_test->test_IntKeyComparator_NoError();

	delete key_test;

    QueryTest * query_test = new QueryTest();
    
    query_test->test_addCondition_NoError();
    query_test->test_evalIntKey_NoError();
    
    delete query_test;
	Test* test;

	test = new KeyTest();
	test->run();

	test = new FileBlocksTest();
	test->run();

	delete test;

    return 0;
}

