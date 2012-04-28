#include "Abstract.h"

class FileSequential: public FileAbstract 
{
    public:

    FileSequential(const char * path, int record_size): FileAbstract(path, record_size) {}
    virtual void create();
    virtual void insert(void * r);
};
