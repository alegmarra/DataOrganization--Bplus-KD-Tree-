#include "UnitTests/KeyTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"

int main()
{
	Test* test;
	test = new KeyTest();
	test->run();
	delete test;

    test = new QueryTest();
    test->run();
	delete test;

	test = new FileBlocksTest();
	test->run();
	delete test;

    test = new SerializersTest();
    test->run();
    delete test;

    return 0;
}

