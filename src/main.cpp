#include "UnitTests/KeyTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"

<<<<<<< HEAD
int main() 
=======


int main()
>>>>>>> 2b426eca9298f825aae6671da5bac6b96ba7440b
{
	Test* test;

	/*
	test = new KeyTest();
	test->run();
<<<<<<< HEAD
	delete test;
	*/
=======
    delete test;
>>>>>>> 2b426eca9298f825aae6671da5bac6b96ba7440b

	test = new FileBlocksTest();
	test->run();
	delete test;

<<<<<<< HEAD
   // test = new QueryTest();
   // test->run();

	//delete test;
=======
    test = new SerializersTest();
    test->run();
    delete test;
>>>>>>> 2b426eca9298f825aae6671da5bac6b96ba7440b

    return 0;
}

