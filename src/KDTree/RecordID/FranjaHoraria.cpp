#include "FranjaHoraria.h"
#include <iostream>
#include <time.h>

FranjaHoraria::FranjaHoraria() : IntKey(8) {}

FranjaHoraria::FranjaHoraria(int_least64_t value) : IntKey(value, 8) {}
#include <cstdlib>

void FranjaHoraria::dump() 
{
    char * from = new char[6];
    char * to = new char[6];
    char * date = new char[12];
    
    time_t from_t = (time_t)(getValue() - 60 * 15);
    time_t to_t   = (time_t)(getValue() + 60 * 15);
    
    strftime(from, 6, "%H:%M", gmtime(&from_t));
    strftime(to, 6, "%H:%M", localtime(&to_t));
    strftime(date, 12, "%d/%m/%Y", localtime(&from_t));

    std::cout << from << " - " << to << " " << date;
}
