#include "UnitTests/KeyTest.cpp"
#include "UnitTests/ConditionTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"
#include "UnitTests/NodeTest.cpp"

#include "File/FileBlocks.h"
#include "KDTree/KD.h"

int main()
{
/*
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
*/

	const char* path = "my_test_file.bin";

	remove(path);


    FileBlocks * f = new FileBlocks(path, 4096);
    KDtree * tree = new KDtree(f);

    std::vector< Record * > records_list;
    tree->load(records_list);


    return 0;
}

