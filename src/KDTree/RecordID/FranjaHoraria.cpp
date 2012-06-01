#include "FranjaHoraria.h"
#include <iostream>

FranjaHoraria::FranjaHoraria() : IntKey(8) {}

FranjaHoraria::FranjaHoraria(int_least64_t value) : IntKey(value, 8) {}
#include <cstdlib>

void FranjaHoraria::dump() 
{
    std::cout << std::endl << "Timestamp: " << getValue() <<std::endl; //<< " | " << getFromHour() << ":";
    exit(2);
}

unsigned FranjaHoraria::getFromHour() 
{
    int_least64_t time = getValue();
    time -= 15 * 60; // Minus 15 minutes
    return time;
};
unsigned FranjaHoraria::getFromMinute() {};
unsigned FranjaHoraria::getToHour() {};
unsigned FranjaHoraria::getToMinute() {};
unsigned FranjaHoraria::getDay() {};
unsigned FranjaHoraria::getMonth() {};
unsigned FranjaHoraria::getYear() {};
