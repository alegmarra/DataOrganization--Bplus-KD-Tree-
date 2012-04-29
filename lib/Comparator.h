
#ifndef COMPARATOR
#define COMPARATOR

class Comparator 
{
    protected:
    void * obj;

    public:
 
    Comparator() { };
    Comparator(void * content);
    virtual int compareTo(void * target) = 0;
};

#endif
