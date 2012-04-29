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

class IntComparator: public Comparator 
{
    public:
    
    IntComparator(void * content) : Comparator(content) { };
    
    int compareTo(void * target) {
        int data =* (int*)obj;
        int targetData =* (int*)target;
        
        if (data == targetData) return 0;
        if (data > targetData) return 1;
        if (data < targetData) return -1;
    }
};

// Very gronch Comparator
class RecordComparator: public Comparator 
{
    public:
    
    RecordComparator(void * content) : Comparator(content) { };
    
    int compareTo(void * target) {
        Record * data = (Record*)obj;
        Record * targetData = (Record*)target;
        bool result;
        
        IntComparator c(&(data->linea));
        result = c.compareTo(&(targetData->linea));
        
        if(result == 0) {
            c.setData(&(data->franja_horaria));
            result = c.compareTo(&(targetData->franja_horaria));
            
            if(result == 0) {
                c.setData(&(data->falla));
                result = c.compareTo(&(targetData->falla));
                
                if (result == 0) {
                    c.setData(&(data->accidente));
                    result = c.compareTo(&(targetData->accidente));
                    
                    if (result == 0) {
                        c.setData(&(data->formacion));
                        result = c.compareTo(&(targetData->formacion));
                    }
                }
            }
        }
        
        return result;
    }
};

int main() 
{
    FileSequential f("/tmp/test.bin", sizeof(Record));
    f.create();
 
    Record a = {1, 2, 3, 4, 5};
    Record b = {6, 7, 8, 9, 0};
    Record c = {1, 5, 3, 4, 2};
    Record d = {6, 7, 8, 9, 0}; // Este no deberia insertarse porque esta repetido
    Record e = {8, 8, 8, 8, 8};

    RecordComparator comp(&a);    
    f.insert(&comp, &a);
    
    comp.setData(&b);    
    f.insert(&comp, &b);

    comp.setData(&c);    
    f.insert(&comp, &c);

    comp.setData(&d);    
    f.insert(&comp, &d);

    comp.setData(&a);
    f.update(&comp, &e);

    comp.setData(&b);
    f.remove(&comp);

    f.reset();
    
    void * ptr = f.next();
    
    while(ptr != NULL) {
        Record x =* (Record*)ptr;
        printf("Linea: %d\n", x.linea);
        printf("Franja horaria: %d\n", x.franja_horaria);
        printf("Falla: %d\n", x.falla);
        printf("Accidente: %d\n", x.accidente);
        printf("Formacion: %d\n", x.formacion);
        printf("===================\n");
        ptr = f.next();
    }
    
    return 0;
}

