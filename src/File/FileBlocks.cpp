/*
 * FileBlocks.cpp
 *
 *  Created on: May 12, 2012
 *      Author: saasbook
 */

#include "FileBlocks.h"
#include <stdlib.h>


void* FileBlocks::find(void* object){


	unsigned blockNumber;

	try{
    	blockNumber = *((unsigned*)object);
    }catch(...){
    	throw InvalidOperationException();
    }

    unsigned offset = (blockNumber * this->blockSize);


    open();
    reset();

    int result = fseek(pFile, offset, SEEK_SET);

    void * buffer;

    // allocate memory to contain the whole file:
    buffer = (void*) malloc (sizeof(char)*blockSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,blockSize,1,pFile);
    if (result != 1) {fputs ("Reading error",stderr); exit (3);}

    /* the whole Block is now loaded in the memory buffer. */

    return buffer;


}


