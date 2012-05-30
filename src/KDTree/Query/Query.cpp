#ifndef KD_TREE_QUERY_CPP
#define KD_TREE_QUERY_CPP

#include "Query.h"
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

int Query::eval(unsigned dimension, Key * k)
{
    std::map< unsigned, std::vector< QueryCondition * > >::iterator it;

    it = conditions.find(dimension);

    if (it != conditions.end()) {
        for (int i = 0; i < it->second.size(); i++) {
            return it->second[i]->eval(k);
        }
    }

    return 0;
}

Query::~Query()
{
    std::map< unsigned, std::vector< QueryCondition * > >::iterator it;

    for(it = conditions.begin(); it != conditions.end(); it++) {
        for (int i = 1; i < it->second.size(); i++) {
            delete it->second[i];
        }
    }
}
#endif
