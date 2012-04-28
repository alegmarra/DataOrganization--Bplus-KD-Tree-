#include "Abstract.h"
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
