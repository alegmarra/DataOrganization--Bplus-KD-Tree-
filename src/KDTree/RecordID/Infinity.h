#ifndef KDTREE_KEY_INFINITY_H
#define KDTREE_KEY_INFINITY_H

#include "Key.h"

class KeyInfinity: public Key
{
private:
    // Infinite keys sholud only be created by QueryCondition to create infinite
    // ranges
    KeyInfinity();
    KeyInfinity(bool positive);

public:
    bool is_positive;

    virtual int compareTo(Key * k);
    virtual std::string getKey();

    virtual int serialize(char* buffer);
    virtual int deserialize(const char* buffer);

    unsigned getSize();

    virtual ~KeyInfinity(){};

    virtual void dump(){};

    friend class QueryCondition;

    // TODO: Remove KeyInfinity from tests and remove the friend test classes
    friend class KeyTest;
};

#endif
