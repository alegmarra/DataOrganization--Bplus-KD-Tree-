#include "Abstract.h"
#include "../Comparator.h"
#include <stdio.h>

FileAbstract::FileAbstract(const char * path, int record_size) 
{
    filename = path;
    length = record_size;
    pFile = NULL;
}
    
FileAbstract::~FileAbstract()
{
    if (pFile) {
        fclose(pFile);
    }
}
    
void FileAbstract::open()
{
    if (!pFile) {
        pFile = fopen(filename, "rb+");
    }        
}

void FileAbstract::reset()
{
    if (!pFile) {
        open();
    } else {
        rewind(pFile);
    }
}
