/*
 * FileBlocks.cpp
 *
 *  Created on: May 12, 2012
 *      Author: AleMarra
 */

#include "FileBlocks.h"
#include <string.h>

FileBlocks::FileBlocks(const char * path, unsigned blockSize)
					   :FileAbstract(path, blockSize){
	this->blockSize = blockSize;

	std::string s = path;
	std::string listPath = s.substr(0, (s.size() -4));

	listPath += "_space.bin";

	fseek(pFile, 0, SEEK_END);
	unsigned fSize = ftell(pFile);
	rewind(pFile);

	if(fSize != 0){
		f_space = fopen(listPath.c_str(), "r+b");

		deserialize();
	}
	else{
		//Reserves block 0 for metadata
		char* buffer = new char[blockSize];

        for (unsigned i = 0; i< blockSize; i++)
            buffer[i] = '#';

		f_space = fopen(listPath.c_str(), "wb+");
		fwrite(buffer, 1, (blockSize-1), f_space);

		//updateSpace(0, (blockSize-1));
		delete[] buffer;
	}

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

void FileBlocks::updateSpace(unsigned blockNumber,unsigned occupied){

	int freeSpace = (blockSize-1) - occupied;

	if(freeSpace < 0)
		throw InvalidOperationException();

	unsigned int size = spaceInBlocks.size();
	if (size == blockNumber)
		spaceInBlocks.push_back(freeSpace);

	else
		spaceInBlocks.at(blockNumber) = freeSpace;
}


/*
 * Only for insertion of new blocks in file
 */
int FileBlocks::insert(void* object, unsigned blockNumber, unsigned insertionSize){

//	if (blockNumber == 0) throw InvalidOperationException();


	char * buffer =(char*) find(&blockNumber);

	if ( buffer != NULL){
		//Block Already exists
		delete[] buffer;
		return 3;
	}

	delete[] buffer;


    size_t result;
	reset();

	//seeks EOF
	result = fseek(pFile, 0, SEEK_END);
	if (result != 0) return 0;


    if (insertionSize < (blockSize-1)){

        buffer = new char[blockSize];

        for (unsigned i = 0; i< insertionSize; i++){
            buffer[i] = ((char*)object)[i];
        }
        buffer [insertionSize] ='\0';

        for (unsigned i = (insertionSize+1); i< blockSize; i++){
            buffer[i] = '#';
        }

    }
    else
        buffer = (char*) object;
	//writes the buffer from blocks beginning
	result = fwrite ( buffer ,1, (blockSize -1), pFile );
    if (result != (blockSize -1)) return result;

    updateSpace(blockNumber, insertionSize);

    delete[] buffer;
    fflush ( pFile );

    //Operation completed with no error


    return 1;

}

/*
 * Updates existing block, no matter if is a free block
 * or an ocuppied block.
 */
int FileBlocks::update(void* object, unsigned blockNumber, unsigned updateSize){

//	if (blockNumber == 0) throw InvalidOperationException();

	char * buffer =(char*) (find(&blockNumber));
	if (!buffer)
		//Block not found
		return 0;
	delete[] buffer;

	size_t result;
	unsigned offset = (blockNumber * (blockSize - 1));

	reset();
	//Seeks blocks beginning
	result = fseek(pFile, offset, SEEK_SET);
	if (result != 0)
		return 0;

	if (updateSize < (blockSize)) {
			buffer = new char[blockSize];
			for (unsigned i = 0; i < updateSize; i++) {
				buffer[i] = ((char*) (object))[i];
			}
			buffer[updateSize] = '\0';
			for (unsigned i = (updateSize + 1); i < blockSize; i++) {
				buffer[i] = '#';
			}
	} else
		buffer = (char*) (object);

	//writes the buffer from blocks beginning
	result = fwrite(buffer, 1, (blockSize - 1), pFile);
	if (result != (blockSize - 1))
		return 0;

	updateSpace(blockNumber, updateSize);

    delete[] buffer;

    if (result != blockSize-1) return 0;

    return 1;
}


int FileBlocks::remove(void* object){

	unsigned* blockNumber = (unsigned*)object;

	char* buffer = (char*)find(blockNumber);
	if ( buffer == NULL )
		//Block not found
		return 0;

	setFree(*blockNumber);
    updateSpace(*blockNumber, 0);

	delete[] buffer;
	return 1;
}


void* FileBlocks::find(void* object){

	//if (*((unsigned*)object) == 0) throw InvalidOperationException();

    reset();

    char* buffer = new char [blockSize];

    // seek blocks begining
	unsigned blockNumber = *((unsigned*)object);
    unsigned offset = (blockNumber * (blockSize-1));

    size_t result = fseek(pFile, offset, SEEK_SET);
    if (result != 0){
    	delete[] buffer;
    	return NULL;
    }

    // copy the block into the buffer:
    result = fread (buffer,1, (blockSize-1) ,pFile);
    if (result != (blockSize-1)){
    	delete[] buffer;
    	return NULL;
    }

    /* the whole block is now loaded in the memory buffer.*/
    return buffer;
}

std::vector<unsigned> FileBlocks::space(){
	return spaceInBlocks;
}


void* FileBlocks::serialize(){

	std::vector<unsigned>::iterator it;

	unsigned* buffer = new unsigned[(blockSize / 4)];
	unsigned j = 0;

	//Begins load of elements
	for (it = spaceInBlocks.begin(); it < spaceInBlocks.end(); it++){
		buffer[j] = *it;
		j++;
	}

	for (j; j<(blockSize / 4); j++)
		buffer[j] = 99999;

	return buffer;
}


void FileBlocks::deserialize(){

	unsigned* buffer = new unsigned[(blockSize / 4)];

	fread(buffer, 4, ((blockSize/4)-1), f_space);

	unsigned i = 0;
	unsigned block = 0;

	while (buffer[i] <= blockSize){
		updateSpace(block,buffer[i]);
		if(buffer[i] == 4095)
			setFree(block);
		block++;
		i++;
	}

	delete[] buffer;
	rewind(f_space);
}

void FileBlocks::deleteData() {
	if (pFile){
	    freopen(filename, "wb+", pFile);
		std::string s = filename;
		std::string listPath = s.substr(0, (s.size() -4));

		listPath += "_space.bin";

		freopen(listPath.c_str(), "wb+", f_space);

		freeBlocksList.clear();
		spaceInBlocks.clear();
	}
	else
	    pFile = fopen(filename, "wb+");
}

FileBlocks::~FileBlocks(){
	void* buffer = serialize();
	rewind(f_space);
	fwrite(buffer, 4, ((blockSize/4)-1), f_space);
	fclose(f_space);
	delete[] (unsigned*)buffer;
}



