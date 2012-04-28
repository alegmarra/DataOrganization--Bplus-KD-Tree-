#include "Sequential.h"

void FileSequential::create() {
    pFile = fopen(filename, "wb");
    fclose(pFile);
    pFile = NULL;
}

void FileSequential::insert(void * r) {
    open();
    // TODO Poner al final
    fwrite(r, length, 1, pFile);
}
