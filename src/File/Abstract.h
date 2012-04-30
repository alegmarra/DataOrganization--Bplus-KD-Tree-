#include <stdio.h>
#include "../Comparator.h"

#ifndef FILE_ABSTRACT
#define FILE_ABSTRACT

class FileAbstract 
{
    protected:

    const char * filename;
    FILE * pFile;
    int length;
    
    void open();
    
    public:
    
    void reset();    
    FileAbstract(const char * path, int record_size);
    ~FileAbstract();
    virtual void create() = 0;
    virtual void insert(Comparator * c, void * r) = 0;
    virtual void update(Comparator * c, void * record) = 0;
    virtual void remove(Comparator * c) = 0;
    virtual void * find(Comparator * target) = 0;
    virtual void * next() = 0;
};


#endif
