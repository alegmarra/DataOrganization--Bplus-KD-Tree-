#include <stdio.h>

class FileAbstract 
{
    protected:

    const char * filename;
    FILE * pFile;
    int length;

    public:

    FileAbstract(const char * path, int record_size) 
    {
        filename = path;
        length = record_size;
        pFile = NULL;
    }
    
    ~FileAbstract()
    {
        if (pFile) {
            fclose(pFile);
        }
    }
    
    void open()
    {
        if (!pFile) {
            pFile = fopen(filename, "rb+");
        }        
    }
    
    virtual void create() = 0;
    virtual void insert(void * r) = 0;
};
