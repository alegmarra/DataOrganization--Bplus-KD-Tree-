#include "Abstract.h"

#ifndef FILE_SEQUENTIAL
#define FILE_SEQUENTIAL

class FileSequential: public FileAbstract 
{
    public:

    FileSequential(const char * path, int record_size): FileAbstract(path, record_size) { };
    virtual void create();
    virtual void insert(Comparator * c, void * r);
    virtual void update(Comparator * c, void * record);
    virtual void remove(Comparator * c);
    virtual void * find(Comparator * target);
    virtual void * next();
    
    bool hasKey(Comparator * c);
};


#endif
