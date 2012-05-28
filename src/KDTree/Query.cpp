#ifndef KD_TREE_QUERY_CPP
#define KD_TREE_QUERY_CPP

#include "KDTree/Query.h"
#include <stdlib.h>
#include <vector>

Query::Query() { }

Query * const Query::addCondition(unsigned dimension, QueryCondition * c)
{
    std::map< unsigned, std::vector< QueryCondition * > >::iterator it;
    
    it = conditions.find(dimension);

    if (it != conditions.end()) {
        it->second.push_back(c);
    } else {
        std::vector< QueryCondition * > v;
        v.push_back(c);
        conditions[dimension] = v;
    }

    return this;
}

unsigned Query::size()
{
    std::map< unsigned, std::vector< QueryCondition * > >::iterator it;
    unsigned size = 0;
   
    for (it = conditions.begin() ; it != conditions.end(); it++) {
        size += it->second.size();
    }
    
    return size;
}

bool Query::eval(unsigned dimension, Key * k)
{
    std::map< unsigned, std::vector< QueryCondition * > >::iterator it;
    
    it = conditions.find(dimension);
    
    if (it != conditions.end()) {
        for (int i = 0; i < it->second.size(); i++) {
            if (!it->second[i]->inRange(k)) {
                return false;
            }
        }
    }
    

    return true;
}

Query::~Query()
{
/*
    for (int i = 1; i < conditions.size(); i++) {
        delete conditions[i];
    }
*/
}

#endif
