#include "UnitTests/KeyTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"

int main() 
{
	Test* test;

	test = new KeyTest();
	test->run();

	test = new FileBlocksTest();
	test->run();

    test = new QueryTest();
    test->run();

	delete test;

    return 0;
}

