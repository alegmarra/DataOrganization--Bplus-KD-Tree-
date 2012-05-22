
#ifndef COMPARATOR
#define COMPARATOR

class Comparator 
{
    private:
    void * obj;

    public:
 
    Comparator(void * content);
    virtual int compareTo(void * target) = 0;
    
    virtual ~Comparator();
};

#endif
