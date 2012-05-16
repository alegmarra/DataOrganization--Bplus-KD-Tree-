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
		FileAbstract(path, blockSize){};

	virtual int insert(void* object, unsigned blockNumber);
	virtual int update(void* object, unsigned blockNumber);
	virtual int remove (void* object);
	virtual void * find(void* object);

	/*
	 * 	Si hay bloques libres, devuelve el primero
	 *
	 * 	Si no hay bloques libres, devuelve el siguiente
	 * 	número a ser ocupado.
	 */
	unsigned getFreeNumber();

	virtual ~FileBlocks(){};

private:
	unsigned blockSize;
	std::list<unsigned> freeBlocksList;
	std::list<unsigned> usedWithSpaceBlocksList;


	void setFree(unsigned blockNumber);

	bool isFree(unsigned* blockNumber);
};

#endif /* FILEBLOCKS_H_ */
