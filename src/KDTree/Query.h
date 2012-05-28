#ifndef KD_TREE_QUERY_H
#define KD_TREE_QUERY_H

#include "Query/Condition.h"
#include<map>
#include<vector>

class Query
{

private:
    std::map< unsigned, std::vector< QueryCondition * > > conditions;

public:

    static const int LOWER = -1;
    static const int HIGHER = 1;
    static const int EQUAL = 0;
    static const int MATCH = 4;

    Query();
    Query * const addCondition(unsigned dimension, QueryCondition * c);
    unsigned size();
    
    /**
     * Evaluates the key against the conditions set for de dimension.
     * Return values:
     *     LOWER: Key is below range, follow the left subtree
     *     HIGHER: Key is above range, move to the right keys
     *     MATCH: Key is in range, or no condition is set for the dimension, 
     *     follow both left and right subtrees
     *     EQUAL: Key matches exactly to the condition. Search follow the right 
     *     subtree
     *
     * @var unsigned dimension Dimension on which to evaluate the key
     * @var Key * k The key being evaluated
     * @return int 
     */
    int eval(unsigned dimension, Key * k);
    virtual ~Query();

};

#endif
