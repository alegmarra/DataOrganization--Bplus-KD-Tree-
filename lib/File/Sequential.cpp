#include "Abstract.h"

class FileSequential: public FileAbstract {

    public:
    
    virtual void create() {
        pFile = fopen(filename, "wb");
        fclose(pFile);
        pFile = NULL;
    }
    
    virtual void insert(void * r) {
        open();
        // TODO Poner al final
        fwrite(r, length, 1, pFile);
    }
};
