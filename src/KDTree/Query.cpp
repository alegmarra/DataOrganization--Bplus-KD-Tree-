#ifndef KD_TREE_QUERY_CPP
#define KD_TREE_QUERY_CPP

#include "KDTree/Query.h"
#include <stdlib.h>
#include <vector>

Query::Query()
{
    conditions = new std::vector<Condition *>;
}

Query * const Query::addCondition(Condition * c)
{
    conditions->push_back(c);
    return this;
}

unsigned Query::size()
{
    return conditions->size();
}

Query::~Query()
{
    for (int i = 1; i < conditions->size(); i++) {
        delete (*conditions)[i];
    }
    
    delete conditions;
}


#endif
