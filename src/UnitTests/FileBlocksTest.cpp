#include "../File/FileBlocks.h"

#include "Test.cpp"
#include <string.h>


class FileBlocksTest: public Test {

private:
	unsigned blockSize;
	const char * path;
	const char * spacePath;

	char* makeBuffer( const char* s,int & size){

		size = strlen(s);
		char* buffer = new char[strlen(s)+1];

        for (unsigned i = 0; i< strlen(s); i++)
        	buffer[i] = s[i];
        buffer[strlen(s)] = '\0';

        return buffer;
	}

public:

	FileBlocksTest(): Test("FileBlocks")
	{

		blockSize = 4096;
		path = "my_FileBlocks_test_file.bin";
		spacePath = "myFileBlocks_test_file_space.bin";

		remove(path);
		remove(spacePath);
	}

	virtual void run(){

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

		test_serialize();

 	}


	void test_Constructor_NewFile(){

        start("Constructor_NewFile");

		remove(path);
		FileAbstract* testFile = new FileBlocks(path, 4096);

		delete testFile;

		FILE* pFile;
		pFile = fopen (path,"r");

		if (!pFile) {
		    fail("File NOT CREATED");
		} else {
    		pass();
		}

		fclose(pFile);
		remove(path);
        
        stop();

	}

	void test_Constructor_ExistingFile()
	{
        start("Constructor_ExistingFile");

		remove(path);
		/*
		 * Create new file, and saves control message
		 */

		FileAbstract* preFile = new FileBlocks(path, 4096);
		//Generates asociated space file;
		delete preFile;

		FILE* pFile;
		pFile = fopen (path,"wb+");
		rewind(pFile);


		int size;
		char* buffer = makeBuffer("Hello World", size);
		fwrite( buffer, 1,(size-1), pFile);
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

		if (!pFile) {
		    fail("File NOT OPEN");
		} else {
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

			if(s.compare("Hello World")) {
				pass();
			}

		}

		delete[] buffer;
		fclose(pFile);
		remove(path);
		
		stop();
	}


    void test_Insert_NoError()
    {
        start("Insert_NoError");
/*
 *      Opens a new file, save data and close the file.
 *      After that, check if the data was succesfully saved.
*/
       //New empty file
   		remove(path);

        FileBlocks* pFile = new FileBlocks(path, blockSize);

       //Generate Buffers for in - out;
        int size;
        char* message = makeBuffer("Hello World", size);

        // Begins insertion
        int result = pFile->insert(message, 0, size);
        if ((result == 3) || (result == 0))	assert(false);

        delete pFile;
        delete[] message;

        //Checks insertion
        FILE* f = fopen(path, "rb+");
        if (!f){
			fail("File NOT OPEN");
        }

        char* buffer = new char[blockSize];

        fread(buffer, 1, (blockSize -1 ),f);

        std::string out = buffer;

        if((out.compare("Hello World") == 0)) {
            pass();
        }

        fclose(f);
		remove(path);

		delete[] buffer;

        stop();
    }

    void test_Insert_BlockAlreadyExists_Error()
    {
        start("Insert_BlockAlreadyExists_Error");
        
        //New empty file
    	remove(path);

        FileBlocks* pFile = new FileBlocks(path, blockSize);

        //Generate Buffers for in - out;

        int size;
        char* buffer = makeBuffer("Hello World", size);

         // Begins insertion
        int result = pFile->insert(buffer, 0, size);
        if ((result == 3) || (result == 0))	assert(false);

         //Re-inserts in the same block
        result = pFile->insert(buffer, 0, size);
        if ((result == 3)) pass();

        else fail("result expected value 3");

        delete pFile;
 		delete[] buffer;
 		remove(path);

        stop();
    }


    void test_Find_NoError()
    {
        start("Find_NoError");
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
            if (!(buffer) ) {
                char msg[50];
                sprintf(msg, "Block %d NOT FOUND", block);
            	fail(msg);
            } else {
                pass();
            }

            out = buffer;
    		delete[] buffer;

            control += s[i];
            if((control.compare(out) == 0)) {
                pass();
            } else {
                fail("Control expected to be equal to out");
            }

        }

		delete pFile;
		remove(path);
		stop();
    }

    void test_Find_NoBlock_Error_EmptyFile()
    {
        start("Find_NoBlock_Error_EmptyFile");
    	/*
    	 * Find on empty file, return NULL
    	 */
		remove(path);

        FileBlocks* pFile = new FileBlocks(path, blockSize);

        unsigned block = 0;
        //Excess by one

        char* buffer = (char*)pFile->find(&block);

        if(buffer == NULL) {
            pass();
        } else {
            fail("File is not empty");
        }

        delete[] buffer;
        delete pFile;
        remove(path);
        stop();
    }

    void test_Find_NoBlock_Error_LoadedFile()
    {
        start("Find_NoBlock_Error_LoadedFile");
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

        if (buffer == NULL) {
            pass();
        } else {
            fail("Block not empty");
        }

        delete[] buffer;
        delete pFile;
        remove(path);
        stop();

    }


    void test_Update_NoError()
    {
        start("Update_NoError");
    	//New empty file
    	remove(path);

    	//Generate Space data
    	FileBlocks* preFile = new FileBlocks(path, blockSize);

    	//Generate data in File
    	int size ;
    	char* message = makeBuffer("Hello World", size);

        preFile->insert(message, preFile->getFreeBlock(), size);
        preFile->insert(message, preFile->getFreeBlock(), size);
        preFile->insert(message, preFile->getFreeBlock(), size);
        preFile->insert(message, preFile->getFreeBlock(), size);

    	delete preFile;
    	delete[] message;


		//Updates file
    	FileBlocks* pFile = new FileBlocks(path, blockSize);



    	char* outBuffer = makeBuffer("GoodBye World", size);

    	size_t result = pFile->update(outBuffer, 1, size);
        if (result != 1) {
            fail("Update failed");
        } else {
            pass();
        }

    	result = pFile->update(outBuffer, 3, size);
    	if (result != 1) {
    	    fail("Update failed");
	    } else {
	        pass();
	    }

    	delete[] outBuffer;
    	delete pFile;


    	std::string out;
    	FILE* f = fopen (path,"rb+");
    	outBuffer = new char[blockSize];

    	for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fread (outBuffer,1,(blockSize-1),f);

	    	out = outBuffer;

	    	switch (i) {
	        	case 0:	
	        	    if((out.compare("Hello World") == 0)) {
	        	        pass();
	        	    } else {
	        	        fail("Expected \"Hello World\"");
	        	    }
	        		break;
	        	case 1: 
	        	    if((out.compare("GoodBye World") == 0)) {
	        	        pass();
	        	    } else {
	        	        fail("Expected \"GoodBye World\"");
	        	    }
	        		break;
	        	case 2: 
	        	    if((out.compare("Hello World") == 0)) {
	        	        pass();
	        	    } else {
	        	        fail("Expected \"Hello World\"");
	        	    }
	        		break;
	        	case 3:	
	        	    if((out.compare("GoodBye World") == 0)) {
	        	        pass();
	        	    } else {
	        	        fail("Expected \"GoodBye World\"");
	        	    }
	        		break;
	    	}
		}
		fclose(f);
		delete[] outBuffer;

		remove(path);

        stop();
    }

    void test_Update_NoBlock_Error()
    {
        start("Update_NoBlock_Error");
    	//New empty file
    	remove(path);

    	//Generate data in File
    	int size;
    	char* buffer = makeBuffer("Hello World", size);

    	FILE* f = fopen (path,"wb+");
		for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fwrite( buffer, 1, (blockSize-1), f);
		}
		fclose(f);
		delete[] buffer;

		//Updates file
    	FileBlocks* pFile = new FileBlocks(path, blockSize);

    	buffer = makeBuffer("GoodBye World", size);

    	int result = pFile->update(buffer, 5, size);
    	if (result != 0){
        	fail("Updates Non-Existent Block");
    	} else {
    	    pass();
	    }

    	delete pFile;
		delete[] buffer;
		remove(path);

        stop();
    }

    void test_GetFreeBlock_WhenNoFreeBlocks(){

        start("GetFreeBlock_WhenNoFreeBlocks");
    	//New empty file
    	remove(path);

    	FileBlocks* pFile = new FileBlocks(path, blockSize);

    	if ((pFile->getFreeBlock()) == 0) {
    	    pass();
	    } else {
    	    fail("Expected Block 0");
    	}
    	
    	delete pFile;


    	//Generate data in File
    	int size;
    	char* buffer = makeBuffer("Hello World", size);

    	FILE* f = fopen (path,"wb+");
		for (int i = 0; i<4; i++){
	    	fseek(f, ((blockSize-1)*i), SEEK_SET);
	    	fwrite( buffer, 1, (blockSize-1), f);
		}
		fclose(f);

    	pFile = new FileBlocks(path, blockSize);
    	unsigned bn = pFile->getFreeBlock();
    	//First free (new block) after existing blocks
    	if (bn == 4) {
    	    pass();
    	} else {
    	    fail("Expected Block 4");
    	}

    	delete pFile;
    	delete[] buffer;
    	remove (path);
        stop();
    }

    void test_Remove_And_GetFree_NoError()
    {
        start("Remove_And_GetFree_NoError");
    	//New empty file
    	remove(path);

		//Removes block number 2
    	FileBlocks* pFile = new FileBlocks(path, blockSize);

    	//Generate data in File
        int size;
        char* buffer = makeBuffer("Hello World", size);

		for (int i = 0; i<4; i++)
			pFile->insert(buffer, i, size);

		//remove block #2
    	unsigned bn = 2;
    	pFile->remove(&bn);

    	//Should return free block instead of new block (# 4)
    	if ((pFile->getFreeBlock()) == 2) {
    	    pass();
    	} else {
    	  fail("Expected Block 4");  
    	}

    	delete pFile;
    	delete[] buffer;
    	remove (path);
        stop();
    }

    void test_Remove_NoBlock_Error()
    {
        start("Remove_NoBlock_Error");
    	remove(path);

    	FileBlocks* pFile = new FileBlocks(path, blockSize);
    	unsigned bn = 4;

    	if ((pFile->remove(&bn)) != 0){
        	fail("Removes Non-Existent Block");
    	} else {
    	    pass();
	    }

    	delete pFile;
    	remove (path);
        stop();
    }

    void test_serialize()
    {
        start("serialize");
    	remove(path);
    	remove(spacePath);

        FileBlocks* pFile = new FileBlocks(path, blockSize);

    	char* buffer = new char[blockSize];
        std::string s = "0123456789";

        for (unsigned i = 0; i< s.size(); i++){

        	buffer[i] = s[i];
        	buffer[(i+1)] = '\0';

        	unsigned bNumber = pFile->getFreeBlock();

            pFile->insert(buffer, bNumber, (i+1));
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
        unsigned size = 1;

        for (it = v.begin(); it<v.end(); it++){
        	if (size == *it) {
        	    pass();
        	} else {
        	    fail("Wrong Size");
        	}
        	
        	size++;
        }

        delete pFile;
        remove(path);
        stop();
    }
};
