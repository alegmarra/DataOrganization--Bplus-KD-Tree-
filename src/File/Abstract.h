#ifndef FILE_ABSTRACT
#define FILE_ABSTRACT
#include <stdlib.h>
#include <stdio.h>
#include <iostream>



//#include "Comparator.h"// Cambio class Comparator; por include,
					   // sino da error en Sequential.cpp
#include "../Exceptions/InvalidOperationException.cpp"

class FileAbstract
{
protected:

    const char * filename;
    FILE * pFile;
    int length;

    void open();
    void reset();
    void close();

public:


	virtual int insert(void* object, unsigned number) =0;
	virtual int update(void* object, unsigned number) =0;
	virtual int remove(void* object) =0;
	virtual void * find(void* object) =0;

	/**
	 * @brief borra todo el contenido
     */
    void deleteData();

public:


    FileAbstract(const char * path, unsigned block_size);
    virtual ~FileAbstract();

};


#endif
