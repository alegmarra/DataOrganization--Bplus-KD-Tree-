#include "Sequential.h"
#include <stdlib.h>

void FileSequential::create() {
    pFile = fopen(filename, "wb");
    fclose(pFile);
    pFile = NULL;
}

void FileSequential::insert(Comparator * c, void * r) {
    open();
    
    if (!hasKey(c)) {
    
        do {
            // Move on...
        } while(next()); 
        
        fwrite(r, length, 1, pFile);
    }
}

bool FileSequential::hasKey(Comparator * c) {
    reset();
    void * obj = next();
    
    while (obj != NULL) {
        if (c->compareTo(obj) == 0) {
            return true;
        }
        
        obj = next();
    }
    
    return false;
}


void FileSequential::update(void * r) {
};

void FileSequential::remove(void * r) {

};

void * FileSequential::find(Comparator* target) {
    open();    
};

void * FileSequential::next() {
    
    void * buffer = (void *) malloc(length);
    fread(buffer, length, 1, pFile);

    if (feof(pFile)) {
        return NULL;
    } else {
        return buffer;
    }
}
