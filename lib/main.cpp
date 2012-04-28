#include "File/Sequential.h"

struct record 
{
    int linea;
    int franja_horaria;
    int falla;
    int accidente;
    int formacion;
};

int main() 
{
    FileSequential f("/tmp/test.bin", sizeof(record));
    f.create();
 
    record a = {1, 5, 3, 4, 2};
    f.insert(&a);
    return 0;
}

