#ifndef KDTREE_KEY_INFINITY_H
#define KDTREE_KEY_INFINITY_H

#include "Key.h"

class KeyInfinity: public Key
{

private:
    bool is_positive;

public:
    KeyInfinity();
    KeyInfinity(bool positive);

    virtual int compareTo(Key * k);
    virtual std::string getKey();

    virtual int serialize(char* buffer);
    virtual int deserialize(const char* buffer);

    virtual ~KeyInfinity(){};

};

#endif
