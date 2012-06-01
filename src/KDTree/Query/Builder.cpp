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
#include <sstream>
#include <iostream>

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

    if (low != "*") {

        if (dimension == "franja"){

        	struct tm tm_dma;
        	struct tm tm_hHigh;
        	struct tm tm_hLow;

        	time_t t_dma;
        	time_t t_hHigh;
        	time_t t_hLow;
        	time_t t_med;

        	//Field example => 12:01 - 12:31 20/05/2012

        	std::string dma = "";

        	dma += low[14]; dma += low[15];
        	dma += " ";
        	dma += low[17]; dma += low[18];
        	dma += " ";
        	dma += low[20]; dma += low[21];
        	dma += low[22]; dma += low[23];
        	//dma += " 01 01 2000" ;

        	std::cout <<"DMA " <<dma<< std::endl;

            if (strptime(dma.c_str(), "%d %m %Y", &tm_dma) == NULL)
                std::cout << "FUUUCK" << std::endl;

            t_dma = mktime(&tm_dma);

            std::cout <<"T DMA " <<t_dma<< std::endl;

        	std::string hLow = "";
        	hLow += low[0];hLow += low[1];
        	hLow += low[2];hLow += low[3];
        	hLow += low[4];
        	hLow+= " 01012000" ;

        	std::cout <<"HLOW " <<hLow<< std::endl;
            if (strptime(hLow.c_str(), "%H:%M %d%m%Y", &tm_hLow) == NULL)
            	std::cout << "FUUUCK" << std::endl;//return NULL;

            t_hLow = mktime(&tm_hLow);

            std::cout <<"T LOW " <<t_hLow<< std::endl;

        	std::string hHigh = "";
        	hHigh += low[8];hHigh += low[9];
        	hHigh += low[10];hHigh += low[11];
        	hHigh += low[12];
        	hHigh += " 01012000" ;

        	std::cout <<"HHIGH " <<hHigh<< std::endl;

            if (strptime(hHigh.c_str(), "%H:%M %d%m%Y", &tm_hHigh) == NULL)
            	std::cout << "FUUUCK" << std::endl;//return NULL;

            t_hHigh = mktime(&tm_hHigh);

			std::cout <<"T HIGH " <<t_hHigh<< std::endl;

            t_med = ((t_hHigh - t_hLow)) + t_dma;


			std::stringstream out;
			out << t_med;
			low = out.str();

			std::cout <<"LOW " <<low<< std::endl;


        }

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

