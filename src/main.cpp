#include "File/Sequential.h"
#include "Comparator.h"

#include "UnitTests/KeyTest.cpp"

struct Record1
{
    int linea;
    int franja_horaria;
    int falla;
    int accidente;
    int formacion;
};


/*
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

        // Error value
        return -2;

    }
};

// Very gronch Comparator


class Record1Comparator: public Comparator
{
    public:
    
    Record1Comparator(void * content) : Comparator(content) { };
    
    int compareTo(void * target) {
        Record1 * data = (Record1*)obj;
        Record1 * targetData = (Record1*)target;
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
*/

int main() 
{
 /*
	FileSequential * f = new FileSequential("/tmp/test.bin", sizeof(Record1));
    f->create();

    Record1 a = {1, 2, 3, 4, 5};
    Record1 b = {6, 7, 8, 9, 0};
    Record1 c = {1, 5, 3, 4, 2};
    Record1 d = {6, 7, 8, 9, 0}; // Este no deberia insertarse porque esta repetido
    Record1 e = {8, 8, 8, 8, 8};

    Record1Comparator comp(&a);
    f->insert(&comp, &a);

    comp.setData(&b);    
    f->insert(&comp, &b);

    comp.setData(&c);    
    f->insert(&comp, &c);

    comp.setData(&d);    
    f->insert(&comp, &d);

    comp.setData(&a);
    f->update(&comp, &e);


    comp.setData(&b);
    f->remove(&comp);

    delete f;


    f = new FileSequential("/tmp/test.bin", sizeof(Record1));
    f->reset();
    
    void * ptr = f->next();
    
    while(ptr != NULL) {
        Record1 x =* (Record1*)ptr;
        printf("Linea: %d\n", x.linea);
        printf("Franja horaria: %d\n", x.franja_horaria);
        printf("Falla: %d\n", x.falla);
        printf("Accidente: %d\n", x.accidente);
        printf("Formacion: %d\n", x.formacion);
        printf("===================\n");
        ptr = f->next();
    }
 */

	KeyTest* test = new KeyTest();

	test->test_StringConstructor_NoError();
	test->test_StringConstructor_Throws_InvalidKeyException();
	test->test_NumberConstructor_NoError();
	test->test_NumberConstructor_Throws_InvalidKeyException();
	test->test_getKey_NoError();
	test->test_KeyComparator_NoError();

	delete test;

    return 0;
}

