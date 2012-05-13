#include <stdio.h>

#ifndef FILE_ABSTRACT
#define FILE_ABSTRACT

//#include "Comparator.h"// Cambio class Comparator; por include,
					   // sino da error en Sequential.cpp
#include "Exceptions/InvalidOperationException.cpp"

class FileAbstract 
{
    protected:

    const char * filename;
    FILE * pFile;
    int length;
    
    public:

    void open();
    void reset();

    virtual void create() =0;
	virtual void insert(void* object) =0;
	virtual void update(void* object) =0;
	virtual void remove(void* object) =0;
	virtual void * find(void* object) =0;
	virtual void * next() =0;

    
    
    FileAbstract(const char * path, unsigned block_size);
    virtual ~FileAbstract();
};


#endif
