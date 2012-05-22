#ifndef KD_TREE_QUERY_H
#define KD_TREE_QUERY_H

#include "KDTree/Query/Condition.h"
#include<vector>

class Query 
{

private:
    std::vector<Condition *> * conditions;

public:
    Query();
    Query * const addCondition(Condition * c);
    unsigned size();
    virtual ~Query();


};

#endif
