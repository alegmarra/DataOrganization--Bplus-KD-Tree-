#ifndef KD_TREE_QUERY_CPP
#define KD_TREE_QUERY_CPP

#include "KDTree/Query.h"
#include <stdlib.h>
#include <vector>

Query::Query()
{
}

Query * const Query::addCondition(QueryCondition * c)
{
    conditions.push_back(c);
    return this;
}

unsigned Query::size()
{
    return conditions.size();
}

Query::~Query()
{
    for (int i = 1; i < conditions.size(); i++) {
        delete conditions[i];
    }

}

bool Query::eval(Key * k)
{
    for (int i = 0; i < conditions.size(); i++) {

        if (!conditions[i]->inRange(k)) {
            return false;
        }
    }

    return true;
}


#endif
