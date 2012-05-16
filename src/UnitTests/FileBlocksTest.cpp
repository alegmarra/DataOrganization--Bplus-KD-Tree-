#include <iostream>
#include <assert.h>

#include "File/FileBlocks.h"
#include "Test.cpp"


class FileBlocksTest: public Test {

public:

	FileBlocksTest(){

		std::cout << "KeyTest BEGIN: "
				  << std::endl << std::endl;
	}

	virtual void run(){
		test_Constructor_NoError();
	}


	void test_Constructor_NoError(){

		FileAbstract* testFile = new FileBlocks("../src/my_test_file.bin", 1024);

		delete testFile;

		FILE* pFile;
		pFile = fopen ("../src/my_test_file.bin","r");


		if (pFile == NULL){
			std::cout << "test_Constructor_NoError: File NOT OPEN"
					  << std::endl;
			assert(false);
		}

		assert(true);
		std::cout << "test_StringConstructor_NoError: OK"
				  << std::endl;

		delete testFile;


	}


	virtual ~FileBlocksTest(){

		std::cout << "-------FileBlocksTest END-------"
				  << std::endl << std::endl;
	}
};
