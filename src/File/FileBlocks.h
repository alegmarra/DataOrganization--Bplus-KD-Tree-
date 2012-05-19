/*
 * FileBlocks.h
 *
 *  Created on: May 12, 2012
 *      Author: AleMarra
 */

#ifndef FILEBLOCKS_H_
#define FILEBLOCKS_H_

#include "Abstract.h"

class FileBlocks: public FileAbstract {
public:
	FileBlocks(const char * path, unsigned blockSize):
		FileAbstract(path, blockSize), blockSize(blockSize){};

	virtual int insert(void* object, unsigned blockNumber);
	virtual int update(void* object, unsigned blockNumber);
	virtual int remove (void* object);
	virtual void * find(void* object);

	/*
	 * 	If there is free blocks, pop's the first in queue
	 *
	 * 	Else, returns next number to be inserted
	 */
	unsigned getFreeBlock();

	virtual ~FileBlocks();

private:
	unsigned blockSize;

	std::list<unsigned> freeBlocksList;

	void setFree(unsigned blockNumber);

	bool isFree(unsigned* blockNumber);
};

#endif /* FILEBLOCKS_H_ */
