#ifndef KD_TREE_QUERY_BUILDER_CPP
#define KD_TREE_QUERY_BUILDER_CPP

#include "Builder.h"
#include "Query.h"
#include "Condition.h"
#include "../RecordID/KeyFactory.h"
#include "../RecordID/Linea.h"
#include "../RecordID/FranjaHoraria.h"
#include "../RecordID/Falla.h"
#include "../RecordID/Accidente.h"
#include "../RecordID/Formacion.h"

#include <string>
#include <map>

QueryBuilder::QueryBuilder()
{
    q = NULL;
}

void QueryBuilder::setQuery(Query * _q)
{
    q = _q;
}

bool QueryBuilder::parse(std::string expr)
{
    std::map< std::string, unsigned > dimensions;
    std::map< std::string, unsigned >::iterator d;
    dimensions["linea"] = LINEA;
    dimensions["franja"] = FRANJA;
    dimensions["falla"] = FALLA;
    dimensions["accidente"] = ACCIDENTE;
    dimensions["formacion"] = FORMACION;
    
    std::string dimension = "";
    char op = 'M'; // (E)qual, (R)ange or (M)issing
    std::string low = "";
    std::string high = "";
    char status = 'D'; // (D)imension, (L)ow, (H)igh or (F)inished
    std::string * container = &dimension;           
    
    for (int c = 0; c < expr.size(); c++) {
    
        char _c = expr[c];
    
        switch(status) {
            case 'D':
                if (_c == '=' || _c == '[') {
                    if (_c == '=') {
                        op = 'E';
                    } else {
                        op = 'R';
                    }
                    container = &low;
                    status = 'L';
                } else {
                    (*container) += tolower(_c);
                }
                break;
                
            case 'L':
                if (_c == ',') {
                    container = &high;
                    status = 'H';
                } else {
                    (*container) += _c;
                }
                break;
                
            case 'H':
                if (_c == ']') {
                    status = 'F';
                } else {
                    (*container) += _c;
                }
                break;
                
            default: break;
        }
        
    }
    
    if (op == 'M') {
        // Missing operator
        return false;
    }

    d = dimensions.find(dimension);

    if (d == dimensions.end()) {
        // Wrong dimension
        return false;
    }
    
    QueryCondition * c = new QueryCondition();
    Key * lowKey;
    Key * hiKey;
    
    if(dimension == "franja"){





    }


    if (low != "*") {
        lowKey = KeyFactory::getKey(dimensions[dimension], low);
        c->setLow(lowKey);
    }
    
    if (op == 'E') {
        c->setHi(lowKey);
    } else if (high != "*") {
        hiKey = KeyFactory::getKey(dimensions[dimension], high);
        c->setHi(hiKey);
    }
    
    
    q->addCondition(d->second, c);
    
    return true;
}

Query * QueryBuilder::getQuery()
{
    return q;
}

#endif

