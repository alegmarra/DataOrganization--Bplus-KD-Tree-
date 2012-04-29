
#ifndef COMPARATOR
#define COMPARATOR

class Comparator 
{
    protected:
    void * obj;

    public:
 
    Comparator(void * content);
    virtual int compareTo(void * target) = 0;
    
    void setData(void * target);
};

#endif
