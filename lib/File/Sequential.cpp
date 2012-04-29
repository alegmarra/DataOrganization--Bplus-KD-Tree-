#include "Sequential.h"
#include <stdlib.h>

void FileSequential::create() {
    pFile = fopen(filename, "wb");
    fclose(pFile);
    pFile = NULL;
}

void FileSequential::insert(Comparator * c, void * r) {
    open();
    reset();
    
    // TODO Poner al final
    fwrite(r, length, 1, pFile);
}


void FileSequential::update(void * r) {
};

void FileSequential::remove(void * r) {

};

void * FileSequential::find(Comparator* target) {
    open();    
};

void * FileSequential::next() {
    open();
    
    void * buffer = (void *) malloc(length);
    fread(buffer, length, 1, pFile);

    if (feof(pFile)) {
        return NULL;
    } else {
        return buffer;
    }
}
