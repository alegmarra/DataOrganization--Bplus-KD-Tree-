#include "UnitTests/KeyTest.cpp"
#include "UnitTests/ConditionTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"
#include "UnitTests/NodeTest.cpp"
#include "UnitTests/KDTreeTest.cpp"

#include "File/FileBlocks.h"
#include "KDTree/KD.h"

int main()
{

	Test* test;
	test = new KeyTest();
	test->run();
	delete test;

    test = new ConditionTest();
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

    test = new NodeTest();
    test->run();
    delete test;

    test = new KDTreeTest();;
    test->run();
    delete test;

    return 0;
}

