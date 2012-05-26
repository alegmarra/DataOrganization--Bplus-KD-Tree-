/*
 * FileBlocks.cpp
 *
 *  Created on: May 12, 2012
 *      Author: AleMarra
 */

#include "FileBlocks.h"
//#include <stdlib.h>

bool FileBlocks::isFree(unsigned* blockNumber){

	std::list<unsigned>::iterator it;

    for ( it = freeBlocksList.begin(); it != freeBlocksList.end(); it++ )
	    if (*it == *blockNumber)
	    	return true;

    return false;

}


void FileBlocks::setFree(unsigned blockNumber){

	freeBlocksList.push_back(blockNumber);
}


unsigned FileBlocks::getFreeBlock(){

	unsigned blockNumber;

	if ( freeBlocksList.empty() ){
		fseek(pFile, 0, SEEK_END);
		unsigned fSize = ftell(pFile);
		rewind(pFile);

		blockNumber = (fSize / (blockSize-1));
		return blockNumber;
	}

	blockNumber = freeBlocksList.front();
	freeBlocksList.pop_front();

	return blockNumber;

}


/*
 * Only for insertion of new blocks in file
 */
int FileBlocks::insert(void* object, unsigned blockNumber){


	if (find(&blockNumber))
		//Block already exists
		return 3;


	size_t result;

	reset();

	//seeks EOF
	result = fseek(pFile, 0, SEEK_END);
	    if (result != 0) return 0;

	char* buffer = (char*) object;

	//writes the buffer from blocks beginning
	result = fwrite ( buffer ,1, (blockSize -1), pFile );
    if (result != (blockSize -1)) return result;

    fflush ( pFile );


    //Operation completed with no error
	return 1;

}

/*
 * Updates existing block, no matter if is a free block
 * or an ocuppied block.
 */
int FileBlocks::update(void* object, unsigned blockNumber){

	if ( find(&blockNumber) == NULL )
		//Block not found
		return 0;

	size_t result;
	unsigned offset = (blockNumber * (blockSize-1));

    reset();

	//Seeks blocks beginning
    result = fseek(pFile, offset, SEEK_SET);
    if (result != 0) return 0;

	char* buffer = (char*) object;

	//writes the buffer from blocks beginning
	result = fwrite ( buffer ,1, (blockSize-1), pFile );
    if (result != blockSize-1) return 0;

    return 1;
}


int FileBlocks::remove(void* object){

	unsigned* blockNumber = (unsigned*)object;

	if ( find(blockNumber) == NULL )
		//Block not found
		return 0;

	setFree(*blockNumber);

	return 1;
}


void* FileBlocks::find(void* object){


    reset();

    char* buffer;
    buffer = new char [blockSize];

    // seek blocks begining
	unsigned blockNumber = *((unsigned*)object);
    unsigned offset = (blockNumber * (blockSize-1));

    size_t result = fseek(pFile, offset, SEEK_SET);
    if (result != 0) return NULL;

    // copy the block into the buffer:
    result = fread (buffer,1, (blockSize-1) ,pFile);
    if (result != (blockSize-1)) return NULL;

    /* the whole block is now loaded in the memory buffer. */
    return buffer;
}

FileBlocks::~FileBlocks(){
}



