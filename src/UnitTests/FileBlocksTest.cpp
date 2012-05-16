#include "File/FileBlocks.h"

#include "Test.cpp"


class FileBlocksTest: public Test {

public:

	FileBlocksTest(){

		std::cout << "FileBlocksTest BEGIN: "
				  << std::endl << std::endl;
	}

	virtual void run(){
		test_Constructor_NewFile();
		test_Constructor_ExistingFile();
	}


	void test_Constructor_NewFile(){

		FileAbstract* testFile = new FileBlocks("my_test_file.bin", 1024);

		delete testFile;

		FILE* pFile;
		pFile = fopen ("my_test_file.bin","r");


		if (!pFile){
			std::cout << "test_Constructor_NewFile: File NOT CREATED"
					  << std::endl;
			assert(false);
		}

		assert(true);
		std::cout << "test_Constructor_NewFile: OK"
				  << std::endl;

		fclose(pFile);
		remove("my_test_file.bin");

	}

	void test_Constructor_ExistingFile(){


		/*
		 * Create new file, and saves control message
		 */
		FILE* pFile;
		pFile = fopen ("my_test_file.bin","wb+");
		rewind(pFile);

		char* buffer = "Hello World";
		fwrite( buffer, 1, sizeof(buffer), pFile);
		fclose(pFile);


		/*
		 * Must open the same file
		 * without deleting any content
		 */
		FileAbstract* testFile = new FileBlocks("my_test_file.bin", 1024);
		delete testFile;

		/*
		 * Opens the file and checks if
		 * control message is OK
		 */
		pFile = fopen ("my_test_file.bin","r");

		if (!pFile){
			std::cout << "test_Constructor_ExistingFile: File NOT OPEN"
					  << std::endl;
			assert(false);
		}
		else{
			rewind(pFile);
			char* message;
			fread (message,1,sizeof(buffer),pFile);

			std::string s = message;

			puts(message);

			assert(s.compare("Hello World"));
				std::cout << "test_Constructor_ExistingFile: OK"
						  << std::endl;

		}






		fclose(pFile);
		remove("my_test_file.bin");

	}


	virtual ~FileBlocksTest(){

		std::cout << "-------FileBlocksTest END-------"
				  << std::endl << std::endl;
	}
};
