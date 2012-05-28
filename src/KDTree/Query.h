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
    Query();
    Query * const addCondition(unsigned dimension, QueryCondition * c);
    unsigned size();
    bool eval(unsigned dimension, Key * k);
    virtual ~Query();


};

#endif
