#ifndef KDTREE_KEY_INFINITY_CPP
#define KDTREE_KEY_INFINITY_CPP

#include "KDTree/Key/Infinity.h"

//#include <iostream>

/*
int KeyInfinity::KeyInfinityComparator::compareTo(void* target)
{
    //bool * pIs_pos = (bool *)is_positive;
    //bool is_pos = *pIs_pos;
    
    std::cout << std::endl << is_pos << std::endl;
    
    if (is_pos) { 
        return -1; // target < +Infinity
    } else {
        return 1; // -Infinity < target
    }
    
	//Error value
	return -2;


}

Comparator * KeyInfinity::getComparator()
{

	return new KeyInfinityComparator(&is_positive);

}

KeyInfinity::KeyInfinityComparator::KeyInfinityComparator(bool is_positive): Comparator(&is_pos)
{
    is_pos = is_positive;
}
*/

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

#endif
