#include <stdio.h>

class FileAccess 
{
    private:
    const char* filename;
    FILE* pFile;
    
    public:
    FileAccess(const char* path) 
    {
        filename = path;
        pFile = NULL;
    }
    
    ~FileAccess()
    {
        if (pFile) {
            fclose(pFile);
        }
    }
    
    void create() 
    {
        open();
    }
    
    void open()
    {
        if (!pFile) {
            pFile = fopen(filename, "w");
        }        
    }
};

int main() 
{
    FileAccess f("/tmp/test.txt");
    f.create();
    return 0;
}
