#ifndef KD_TREE_QUERY_CONDITION_CPP
#define KD_TREE_QUERY_CONDITION_CPP

#include "../RecordID/Key.h"
#include "../RecordID/Infinity.h"
#include "../Query.h"
#include "../Query/Condition.h"
#include "../../Exceptions/InvalidConditionRangeException.h"


QueryCondition::QueryCondition()
{
    init();
};

QueryCondition::QueryCondition(Key * equal) 
{
    low_key = equal;
    hi_key = equal;
}

QueryCondition::QueryCondition(Key * low, Key * hi)
{
    init();
    setLow(low);
    setHi(hi);
};

void QueryCondition::init()
{
    low_key = new KeyInfinity();
    hi_key = new KeyInfinity(true);
}

QueryCondition * const QueryCondition::setLow(Key * k)
{
    if (hi_key->compareTo(k) < 0) {
        throw InvalidConditionRangeException();
    } 
    
    delete low_key;
    low_key = k;
    return this;
}

QueryCondition * const QueryCondition::setHi(Key * k)
{
    if (low_key->compareTo(k) > 0) {
        throw InvalidConditionRangeException();
    } 
    
    delete hi_key;
    hi_key = k;
    return this;
}

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

QueryCondition::~QueryCondition()
{
    if (low_key == hi_key) {
        delete low_key;
    } else {
        delete low_key;
        delete hi_key;
    }
}

#endif
