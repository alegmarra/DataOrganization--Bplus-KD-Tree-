#ifndef FRANJA_HORARIA_H
#define FRANJA_HORARIA_H

#define FRANJA 1

#include "IntKey.h"

/**
 * Time stored as a Unix timestamp in UT
 * http://en.wikipedia.org/wiki/Unix_time
 *
 * The stored value represents the midpoint of a 30 minutes time frame
 */ 
class FranjaHoraria : public IntKey {
    public:
        FranjaHoraria();
        FranjaHoraria(int_least64_t value);
        virtual void dump() ;
        
        unsigned getFromHour();
        unsigned getFromMinute();
        unsigned getToHour();
        unsigned getToMinute();
        unsigned getDay();
        unsigned getMonth();
        unsigned getYear();
};

#endif  // FRANJA_HORARIA_H
