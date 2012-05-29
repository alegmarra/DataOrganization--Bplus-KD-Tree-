/*
 * FileBlocks.h
 *
 *  Created on: May 12, 2012
 *      Author: AleMarra
 */
#ifndef FILEBLOCKS_H_
#define FILEBLOCKS_H_

#include "Abstract.h"
#include <list>
#include <vector>

class FileBlocks: public FileAbstract {
public:
	FileBlocks(const char * path, unsigned blockSize);

	virtual int insert(void* object, unsigned blockNumber, unsigned insertionSize);
	virtual int update(void* object, unsigned blockNumber, unsigned updateSize);
	virtual int remove (void* object);
	virtual void * find(void* object);
	void deleteData();
	/*
	 * 	If there is free blocks, pop's the first in queue
	 *
	 * 	Else, returns next number to be inserted
	 */
	unsigned getFreeBlock();

	unsigned getBlockSize();

	virtual ~FileBlocks();

	// DO NOT USE THIS METHOD
    std::vector<unsigned> space();
    // REMOVE


private:
	unsigned blockSize;
	std::list<unsigned> freeBlocksList;

	//vector.at(n) has the remaining space in the n block
    std::vector<unsigned> spaceInBlocks;
    FILE* f_space;
    void setFree(unsigned blockNumber);
	void updateSpace(unsigned blockNumber, unsigned occupied);

	virtual void* serialize();
	virtual void deserialize();


};

#endif /* FILEBLOCKS_H_ */
