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

    /**
     * Initializes the Condition with an infinite Range
     */
    QueryCondition();
    
    /**
     * Initializes the condition for an EQUAL Match (low == hi)
     *
     * @param Key * equal
     */
    QueryCondition(Key * equal);

    /**
     * Initializes the condition for a range
     *
     * @param Key * low
     * @param Key * hi
     * @throws InvalidConditionRangeException if low > hi
     */
    QueryCondition(Key * low, Key * hi);
    QueryCondition(KeyInfinity * low, Key * hi);
    QueryCondition(Key * low, KeyInfinity * hi);
    QueryCondition(KeyInfinity * low, KeyInfinity * hi);

    /**
     * Replaces the lower key.
     *
     * @param Key * k
     * @return QueryCondition
     * @throws InvalidConditionRangeException if k > hi_key
     */
    QueryCondition * const setLow(KeyInfinity * k);
    QueryCondition * const setLow(Key * k);

    /**
     * Replaces the higher key.
     *
     * @param Key * k
     * @return QueryCondition
     * @throws InvalidConditionRangeException if k < low_key
     */
    QueryCondition * const setHi(KeyInfinity * k);
    QueryCondition * const setHi(Key * k);

    /**
     * Checks that the given key is within the condition range
     *
     * @deprecated
     * @param Key * k
     * @return bool
     */
    bool inRange(Key * k);

    /**
     * Evaluates the condition against a key. This method is used by the 
     * Query::eval() method and returns one of the Query constants
     *
     * @see Query::eval()
     * @param Key * k
     * @return int
     */
    int eval(Key * k);

    /**
     * Destructor. Deletes both high and low keys
     */
    virtual ~QueryCondition();

private:

    void init();
};

#endif
