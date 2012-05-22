#ifndef KD_TREE_QUERY_CONDITION_CPP
#define KD_TREE_QUERY_CONDITION_CPP

#include "KDTree/Key.h"
#include "KDTree/Query/Condition.h"

//#include <iostream>

QueryCondition::QueryCondition() 
{
    QueryCondition(new KeyInfinity(), new KeyInfinity(true));
};

QueryCondition::QueryCondition(Key * low, Key * hi) 
{
    low_key = low;
    hi_key = hi;
};

bool QueryCondition::inRange(Key * k)
{
    /*
    // Requiere iostream para testear
    char s[3];
    s[0] = '<';
    s[1] = '=';
    s[2] = '>';

    std::cout << "Low: " << low_key->getKey() << s[low_key->getComparator()->compareTo(k) + 1] << k->getKey() << std::endl;
    std::cout << "High: " << hi_key->getKey() << s[hi_key->getComparator()->compareTo(k) + 1] << k->getKey() << std::endl;
    std::cout << std::endl;
    */
    
    return low_key->getComparator()->compareTo(k) < 1 && hi_key->getComparator()->compareTo(k) > -1;
};

#endif
