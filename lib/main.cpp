#include "File/Sequential.h"
#include "Comparator.h"

struct Record 
{
    int linea;
    int franja_horaria;
    int falla;
    int accidente;
    int formacion;
};

class RecordComparator: public Comparator {

    public:
    
    RecordComparator(void * content) : Comparator(content) { };
    
    int compareTo(void * target) {
        Record * data = obj;
        Record * targetData = target;
        
        if (data->linea == targetData->linea) {
            printf("%d == %d\n", data->linea, targetData->linea);
            return 0;
        }
        
        if (data->linea > targetData->linea) {
            printf("%d > %d\n", data->linea, targetData->linea);
            return 1;
        }
        
        if (data->linea < targetData->linea) {
            printf("%d < %d\n", data->linea, targetData->linea);
            return -1;
        }
    }
};

int main() 
{
    FileSequential f("/tmp/test.bin", sizeof(Record));
    f.create();
 
    Record a = {1, 2, 3, 4, 5};
    Record b = {6, 7, 8, 9, 0};
    Record c = {1, 5, 3, 4, 2};

    RecordComparator aComp(&a);    
    f.insert(&aComp, &a);
    
    RecordComparator bComp(&b);    
    f.insert(&bComp, &b);

    RecordComparator cComp(&c);    
    f.insert(&cComp, &c);

    f.reset();
    
    void * ptr = f.next();
    
    while(ptr != NULL) {
        Record x =* (Record*)ptr;
        printf("Linea: %d\n", x.linea);
        ptr = f.next();
    }
    
    return 0;
}

