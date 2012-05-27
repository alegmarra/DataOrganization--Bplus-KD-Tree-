#include "Abstract.h"
#include "../Comparator.h"

FileAbstract::FileAbstract(const char * path, unsigned block_size){
    filename = path;
    length = block_size;
    pFile = NULL;

    open();
}

<<<<<<< HEAD

=======
>>>>>>> 2b426eca9298f825aae6671da5bac6b96ba7440b
FileAbstract::~FileAbstract(){
	close();
}

void FileAbstract::open()
{
    if (!pFile) {
        pFile = fopen(filename, "rb+");

        if(!pFile)
        	//No file, creates a new file and
        	//opens it for reading or writing
        	pFile = fopen(filename, "wb+");
    }
}

void FileAbstract::close(){
    if (pFile) {
        fclose(pFile);
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

void FileAbstract::deleteData() {
    if (pFile)
        pFile = freopen(filename, "wb+", pFile);
    else
        pFile = fopen(filename, "wb+");
}
