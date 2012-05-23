#include "UnitTests/KeyTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"

#include <iostream>

int main() 
{
	Test* test;

	test = new KeyTest();
	test->run();
    delete test;

	test = new FileBlocksTest();
	test->run();
    delete test;

    test = new QueryTest();
    test->run();
	delete test;

    std::cout << std::endl << "UnitTest END" 
               << std::endl << std::endl;

    return 0;
}

