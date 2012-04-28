#include <stdio.h>

#ifndef FILE_ABSTRACT
#define FILE_ABSTRACT

class FileAbstract 
{
    protected:

    const char * filename;
    FILE * pFile;
    int length;
    
    public:
    
    FileAbstract(const char * path, int record_size);
    ~FileAbstract();
    void open();    
    virtual void create() = 0;
    virtual void insert(void * r) = 0;
};


#endif
