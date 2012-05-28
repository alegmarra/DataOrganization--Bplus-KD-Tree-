#ifndef KDTREE_QUERY_CONDITION_H
#define KDTREE_QUERY_CONDITION_H

#include "../RecordID/Key.h"
#include "../RecordID/Infinity.h"

class QueryCondition
{

private:
    Key * low_key;
    Key * hi_key;

public:
    QueryCondition();
    QueryCondition(Key * low, Key * hi);
    bool inRange(Key * k);
};

#endif
