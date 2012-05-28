#ifndef KDTREE_KEY_INFINITY_H
#define KDTREE_KEY_INFINITY_H

#include "Key.h"


class KeyInfinity: public Key
{

private:
    bool is_positive;

public:
    KeyInfinity();//: Key("ZZZZ") { KeyInfinity(false); };
    KeyInfinity(bool positive);//: Key("ZZZZZ") { is_positive = positive; };

    virtual int compareTo(Key * k);
    virtual std::string getKey();
    //Comparator* getComparator();

    virtual int serialize(char* buffer);
    virtual int deserialize(const char* buffer);



    virtual ~KeyInfinity(){};



private:
/*
class KeyInfinityComparator: public Comparator
{

private:
bool is_pos;

public:
KeyInfinityComparator(bool is_positive);
virtual int compareTo(void * target);


};

*/
};

#endif
