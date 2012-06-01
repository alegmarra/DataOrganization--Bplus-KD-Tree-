#ifndef KD_TREE_QUERY_BUILDER_H
#define KD_TREE_QUERY_BUILDER_H

#include "Query.h"
#include "Condition.h"
#include <string>

/**
 * Used to build a query from CLI arguments. Does not handle query instantiation
 * or destruction
 */
class QueryBuilder {

private:
    Query * q;

public:

    QueryBuilder();

    /**
     * Set the query to build upon
     *
     * @return void
     */ 
    void setQuery(Query * _q);
    
    /**
     * Parse the expresion into a condition. Returns false if something went
     * wrong
     *
     * @param std::string expr The expresion to be parsed
     * @return bool
     */
    bool parse(std::string expr);
    
    /**
     * Fetch the constructed Query
     *
     * @return Query *
     */
    Query * getQuery();
    
};

#endif
