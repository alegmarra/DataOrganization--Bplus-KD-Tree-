/*
 * FileBlocks.h
 *
 *  Created on: May 12, 2012
 *      Author: saasbook
 */

#ifndef FILEBLOCKS_H_
#define FILEBLOCKS_H_

#include "Abstract.h"

class FileBlocks: public FileAbstract {
public:
	FileBlocks(const char * path, unsigned blockSize):
		FileAbstract(path, blockSize){};

	virtual void create();
	virtual void insert(void* object);
	virtual void update(void* object);
	virtual void remove(void* object);
	virtual void * find(void* object);
	virtual void * next();

	virtual ~FileBlocks();

private:
	unsigned blockSize;
};

#endif /* FILEBLOCKS_H_ */
