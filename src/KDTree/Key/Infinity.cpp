#ifndef KDTREE_KEY_INFINITY_CPP
#define KDTREE_KEY_INFINITY_CPP

#include "KDTree/Key/Infinity.h"

int KeyInfinity::KeyInfinityComparator::compareTo(void* target)
{
    bool * pIs_pos = (bool *)is_positive;
    bool is_pos = *pIs_pos;
    
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



#endif
