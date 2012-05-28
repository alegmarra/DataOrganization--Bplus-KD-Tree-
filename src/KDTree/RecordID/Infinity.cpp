#ifndef KDTREE_KEY_INFINITY_CPP
#define KDTREE_KEY_INFINITY_CPP

#include "KDTree/RecordID/Infinity.h"

KeyInfinity::KeyInfinity()
{
    KeyInfinity(false);
}

KeyInfinity::KeyInfinity(bool positive)
{
    is_positive = positive;
}

int KeyInfinity::compareTo(Key * k)
{
    if (is_positive) {
        return 1;
    } else {
        return -1;
    }
}

std::string KeyInfinity::getKey()
{
    if (is_positive) {
        return "+Inf";
    } else {
        return "-Inf";
    }
}

int KeyInfinity::serialize(char* buffer){

	return 0;
}

int KeyInfinity::deserialize(const char* buffer){

	return 0;
}


#endif

