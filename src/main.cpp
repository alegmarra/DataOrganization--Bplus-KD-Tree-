#include "UnitTests/KeyTest.cpp"
#include "UnitTests/QueryTest.cpp"

struct Record1
{
    int linea;
    int franja_horaria;
    int falla;
    int accidente;
    int formacion;
};


int main() 
{

	KeyTest * key_test = new KeyTest();

	key_test->test_StringConstructor_NoError();
	key_test->test_StringConstructor_Throws_InvalidKeyException();
	key_test->test_NumberConstructor_NoError();
	key_test->test_NumberConstructor_Throws_InvalidKeyException();
	key_test->test_getKey_NoError();
	key_test->test_KeyComparator_NoError();

	delete key_test;

    QueryTest * query_test = new QueryTest();
    
    query_test->test_addCondition_NoError();
    
    //delete query_test;

    return 0;
}

