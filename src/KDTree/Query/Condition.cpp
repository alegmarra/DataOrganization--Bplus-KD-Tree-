#ifndef KD_TREE_QUERY_CONDITION_CPP
#define KD_TREE_QUERY_CONDITION_CPP

#include "../RecordID/Key.h"
#include "../Query.h"
#include "../Query/Condition.h"


QueryCondition::QueryCondition()
{
};

QueryCondition::QueryCondition(Key * low, Key * hi)
{
    low_key = low;
    hi_key = hi;
};

bool QueryCondition::inRange(Key * k)
{
    return low_key->compareTo(k) <= 0 && hi_key->compareTo(k) >= 0;
};

int QueryCondition::eval(Key * k)
{
    int comp_low = low_key->compareTo(k);
    int comp_high = hi_key->compareTo(k);
    
    if (comp_low > 0) { // Lower end is higher than key
        return Query::LOWER;
    } else if (comp_high < 0) { // Higher end is lower than key
        return Query::HIGHER;
    } else if(comp_low == comp_high && comp_low == 0) { // Key matches exactly both ends
        return Query::EQUAL;    
    } else {
        return Query::MATCH;
    }
}

#endif
