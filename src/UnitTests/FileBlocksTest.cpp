#include "../File/FileBlocks.h"

#include "Test.cpp"
#include <string.h>


class FileBlocksTest: public Test {

private:
	unsigned blockSize;
	const char * path;

	char* makeBuffer(const char* s){

        char* buffer = new char[20];//blockSize];

        for (unsigned i = 0; i< strlen(s); i++)
        	buffer[i] = s[i];
        buffer[strlen(s)] = '\0';

        return buffer;
	}

public:

	FileBlocksTest(){

		blockSize = 4096;
		path = "my_test_file.bin";

		std::cout << std::endl << "FileBlocksTest BEGIN: "
				  << std::endl << std::endl;
	}

	virtual void run(){
/*
		test_Constructor_NewFile();

		test_Constructor_ExistingFile();

		test_Insert_NoError();

		test_Insert_BlockAlreadyExists_Error();

		test_Find_NoError();

		test_Find_NoBlock_Error_EmptyFile();

		test_Find_NoBlock_Error_LoadedFile();

        test_Update_NoError();

		test_Update_NoBlock_Error();

		test_GetFreeBlock_WhenNoFreeBlocks();

		test_Remove_And_GetFree_NoError();

		test_Remove_NoBlock_Error();
*/
		test_serialize();

 	}


	void test_Constructor_NewFile(){

		FileAbstract* testFile = new FileBlocks(path, 4096);

		delete testFile;

		FILE* pFile;
		pFile = fopen (path,"r");


		if (!pFile){
			std::cout << "test_Constructor_NewFile: File NOT CREATED"
					  << std::endl;
			assert(false);
		}

		assert(true);
		std::cout << "test_Constructor_NewFile: OK"
				  << std::endl;

		fclose(pFile);
		remove(path);

	}

	void test_Constructor_ExistingFile(){

		/*
		 * Create new file, and saves control message
		 */
		FILE* pFile;
		pFile = fopen (path,"wb+");
		rewind(pFile);

		char* buffer = makeBuffer("Hello World");
		fwrite( buffer, 1,(strlen(buffer)-1), pFile);
		fclose(pFile);

		/*
		 * Must open the same file
		 * without deleting any content
		 */
		FileAbstract* testFile = new FileBlocks(path, 4096);
		delete testFile;

		/*
		 * Opens the file and checks if
		 * control message is OK
		 */
		pFile = fopen (path,"r");

		if (!pFile){
			std::cout << "test_Constructor_ExistingFile: File NOT OPEN"
					  << std::endl;
			assert(false);
		}
		else{
			rewind(pFile);
			char* output = new char [strlen(buffer)];

			size_t result = fread (output,1,(strlen(buffer)-1),pFile);
			if (result != (strlen(buffer)-1)){
				delete[] buffer;
				delete[] output;
 				assert(false);
			}
			std::string s = output;
			delete[] output;

			assert(s.compare("Hello World"));
				std::cout << "test_Constructor_ExistingFile: OK"
						  << std::endl;

		}

		delete[] buffer;
		fclose(pFile);
		remove(path);
	}


    void test_Insert_NoError(){

/*
 *      Opens a new file, save data and close the file.
 *      After that, check if the data was succesfully saved.
*/
       //New empty file
   		remove(path);

        FileBlocks* pFile = new FileBlocks(path, blockSize);

       //Generate Buffers for in - out;
        char* message = makeBuffer("Hello World");

        // Begins insertion
        int result = pFile->insert(message, 0);
        if ((result == 3) || (result == 0))	assert(false);

        delete pFile;
        delete[] message;

        //Checks insertion
        FILE* f = fopen(path, "rb+");
        if (!f){
			std::cout << "test_Insert_NoError: File NOT OPEN"
					  << std::endl;
			assert(false);
        }

        char* buffer = new char[blockSize];

        fread(buffer, 1, (blockSize -1 ),f);

        std::string out = buffer;

        std::cout  << out << std::endl;
        assert((out.compare("Hello World") == 0));

        std::cout << "test_Insert_NoError: OK"
				  << std::endl;

        fclose(f);
		remove(path);

		delete[] buffer;

        }

    void test_Insert_BlockAlreadyExists_Error(){
        //New empty file
    	remove(path);
        
        FileBlocks* pFile = new FileBlocks(path, blockSize);

        //Generate Buffers for in - out;
        char* buffer = makeBuffer("Hello World");

         // Begins insertion
        int result = pFile->insert(buffer, 0);
        if ((result == 3) || (result == 0))	assert(false);

         //Re-inserts in the same block
        result = pFile->insert(buffer, 0);
        if ((result == 3)) assert(true);

        else assert(false);
        std::cout << "test_Insert_BlockAlreadyExists_Error: OK"
				  << std::endl;

        delete pFile;
 		delete[] buffer;
 		remove(path);

    }


    void test_Find_NoError(){

    	/*
    	 * Open file with data on block n,
    	 * return the block.
    	 */
		remove(path);

       //Generate Buffers for in - out;
        char* buffer = new char[blockSize];

        std::string s = "0123456789";

        FILE* f;
		f = fopen (path,"wb+");
		rewind(f);

        for (unsigned i = 0; i< s.size(); i++){

        	buffer[i] = s[i];
        	buffer[(i+1)] = '\0';
            for (unsigned j = (i+2); j< blockSize; j++){
                buffer[j] = '#';
            }
        	fseek(f, ((blockSize-1)*i), SEEK_SET);
        	fwrite( buffer, 1, (blockSize-1), f);

        	//first (#0) block has '0', second (#1) has '01', etc
        }

        delete[] buffer;
        fclose(f);
        //File filled with data and closed

        //Opens the file, finds the written blocks and checks espected data
        FileBlocks* pFile = new FileBlocks(path, blockSize);

        unsigned block;
        std::string out;
        std::string control = "";

        for (unsigned i = 0; i<s.size(); i++){
        	block = i;
            buffer = (char*)pFile->find(&block);
            if ( !(buffer) ){
            	std::cout << "test_Find_NoError: Block " << block << " NOT FOUND"
            			  << std::endl;
        		assert(false);
            }

            out = buffer;
    		delete[] buffer;

            control += s[i];
            assert((control.compare(out) == 0));

        }

        std::cout << "test_Find_NoError: OK" << std::endl;

		delete pFile;
		remove(path);
    }

    void test_Find_NoBlock_Error_EmptyFile(){

    	/*
    	 * Find on empty file, return NULL
    	 */
		remove(path);

        FileBlocks* pFile = new FileBlocks(path, blockSize);

        unsigned block = 0;
        //Excess by one

        char* buffer = (char*)pFile->find(&block);

        assert (buffer == NULL);
        std::cout << "test_Find_NoBlock_Error_EmptyFile: OK" << std::endl;

        delete[] buffer;
        delete pFile;
        remove(path);

    }

    void test_Find_NoBlock_Error_LoadedFile(){

    	/*
    	 * Open file with no data on block n+1,
    	 * return NULL
    	 */
		remove(path);
        char* buffer = new char[blockSize];

       //Generate Buffers for in - out;
        std::string s = "0123456789";

        FILE* f;
		f = fopen (path,"wb+");
		rewind(f);

        for (unsigned i = 0; i<5; i++){
        	buffer[i] = s[i];
        	buffer[(i+1)] = '\0';
        	for(unsigned j =(i+2); j<blockSize; j++)
        		buffer[j] = '#';

        	fseek(f, ((blockSize-1)*i), SEEK_SET);
        	fwrite( buffer, 1, (blockSize-1), f);
        	//first (#0) block has '0', second (#1) has '01', etc
        }
        fclose(f);
        delete[] buffer;
        //File filled with data and closed


        FileBlocks* pFile = new FileBlocks(path, blockSize);

        unsigned block = 4;
        //Excess by one
        block++;

        buffer = (char*)pFile->find(&block);

        assert (buffer == NULL);
        std::cout << "test_Find_NoBlock_Error_LoadedFile: OK" << std::endl;

        delete[] buffer;
        delete pFile;
        remove(path);

    }


    void test_Update_NoError(){

    	//New empty file
    	remove(path);

    	//Generate data in File
        char* message = makeBuffer("Hello World");

        char* buffer ;

        if (strlen(message) < (blockSize)){

            buffer = new char[blockSize];
            for (unsigned i = 0; i< strlen(message); i++)
                buffer[i] = message[i];

            buffer [strlen(message)] ='\0';

            for (unsigned i = (strlen(message)+1); i< blockSize; i++)
                buffer[i] = '#';

            delete[] message;
        }
        else
           buffer = (char*) message;



    	FILE* f = fopen (path,"wb+");
		for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fwrite( buffer, 1, (blockSize-1), f);
		}
		fclose(f);

		//Updates file
    	FileBlocks* pFile = new FileBlocks(path, blockSize);
    	delete[] buffer;


    	char* outBuffer = makeBuffer("GoodBye World");

    	size_t result = pFile->update(outBuffer, 1);
        if (result != 1) assert (false);

    	pFile->update(outBuffer, 3);

    	delete[] outBuffer;

    	delete pFile;


    	std::string out;
    	f = fopen (path,"rb+");
    	outBuffer = new char[blockSize];

    	for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fread (outBuffer,1,(blockSize-1),f);

	    	out = outBuffer;

	    	switch (i){
	    	case 0:	assert((out.compare("Hello World") == 0));
	    		break;
	    	case 1: assert((out.compare("GoodBye World") == 0));
	    		break;
	    	case 2: assert((out.compare("Hello World") == 0));
	    		break;
	    	case 3:	assert((out.compare("GoodBye World") == 0));
	    		break;
	    	}
		}
		fclose(f);

		delete[] outBuffer;

		remove(path);

        std::cout << "test_Update_NoError: OK" << std::endl;

    }

    void test_Update_NoBlock_Error(){

    	//New empty file
    	remove(path);

    	//Generate data in File
        char* buffer = makeBuffer("Hello World");

    	FILE* f = fopen (path,"wb+");
		for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fwrite( buffer, 1, (blockSize-1), f);
		}
		fclose(f);
		delete[] buffer;

		//Updates file
    	FileBlocks* pFile = new FileBlocks(path, blockSize);

    	buffer = makeBuffer("GoodBye World");

    	int result = pFile->update(buffer, 5);
    	if (result != 0){
        	std::cout << "test_Update_NoBlock_Error: Updates Non-Existent Block"
        			  << std::endl;
    		assert(false);
    	}

    	assert(true);

    	delete pFile;
		delete[] buffer;
		remove(path);

        std::cout << "test_Update_NoBlock_Error: OK" << std::endl;
    }

    void test_GetFreeBlock_WhenNoFreeBlocks(){

    	//New empty file
    	remove(path);

    	FileBlocks* pFile = new FileBlocks(path, blockSize);

    	assert ((pFile->getFreeBlock()) == 0);
    	delete pFile;


    	//Generate data in File
        char* buffer = makeBuffer("Hello World");

    	FILE* f = fopen (path,"wb+");
		for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fwrite( buffer, 1, (blockSize-1), f);
		}
		fclose(f);

    	pFile = new FileBlocks(path, blockSize);
    	unsigned bn = pFile->getFreeBlock();
    	//First free (new block) after existing blocks
    	assert (bn == 4);

        std::cout << "test_GetFreeBlock_WhenNoFreeBlocks: OK" << std::endl;

    	delete pFile;
    	delete[] buffer;
    	remove (path);

    }

    void test_Remove_And_GetFree_NoError(){

    	//New empty file
    	remove(path);

    	//Generate data in File
        char* buffer = makeBuffer("Hello World");

    	FILE* f = fopen (path,"wb+");
		for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fwrite( buffer, 1, (blockSize-1), f);
		}
		fclose(f);

		//Removes block number 2
    	FileBlocks* pFile = new FileBlocks(path, blockSize);

    	unsigned bn = 2;
    	pFile->remove(&bn);

    	//Should return free block instead of new block (# 4)
    	assert ((pFile->getFreeBlock()) == 2);

        std::cout << "test_Remove_And_GetFree_NoError: OK" << std::endl;

    	delete pFile;
    	delete[] buffer;
    	remove (path);
    }

    void test_Remove_NoBlock_Error(){

    	remove(path);

    	FileBlocks* pFile = new FileBlocks(path, blockSize);
    	unsigned bn = 4;

    	if ((pFile->remove(&bn)) != 0){
        	std::cout << "test_Remove_NoBlock_Error: Removes Non-Existent Block"
        			  << std::endl;
    		assert(false);
    	}
    	assert(true);
        std::cout << "test_Remove_NoBlock_Error: OK" << std::endl;

    	delete pFile;
    	remove (path);

    }

    void test_serialize(){

    	remove(path);

        FileBlocks* pFile = new FileBlocks(path, blockSize);

    	char* buffer = new char[blockSize];
        std::string s = "0123456789";

        for (unsigned i = 0; i< s.size(); i++){

        	buffer[i] = s[i];
        	buffer[(i+1)] = '\0';

        	unsigned bNumber = pFile->getFreeBlock();

            pFile->insert(buffer, bNumber);
        	//first (#0) block has '0', second (#1) has '01', etc
        }


        delete[] buffer;
        delete pFile;

        /*
         * File left with 10 blocks of sizes
         * 1, 2, 3...10 bytes occupied
         */

        pFile = new FileBlocks(path, blockSize);
        std::vector<unsigned> v = pFile->space();
        std::vector<unsigned>::iterator it;
        int size = 1;

        for (it = v.begin(); it<v.end(); it++){
        	assert (size == *it);
        	size++;
        }

        delete pFile;
        remove(path);
    }

    virtual ~FileBlocksTest(){

		std::cout << "-------FileBlocksTest END-------"
				  << std::endl;
	}
};
