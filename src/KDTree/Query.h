#ifndef KD_TREE_QUERY_H
#define KD_TREE_QUERY_H

#include "Query/Condition.h"
#include<vector>

class Query
{

private:
    //std::vector<QueryCondition *> * conditions;
    std::vector<QueryCondition *> conditions;

public:
    Query();
    Query * const addCondition(QueryCondition * c);
    unsigned size();
    bool eval(Key * k);
    virtual ~Query();


};

#endif
