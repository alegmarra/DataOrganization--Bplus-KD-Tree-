#include "FranjaHoraria.h"

FranjaHoraria::FranjaHoraria() : IntKey(8) {}

FranjaHoraria::FranjaHoraria(int_least64_t value) : IntKey(value, 8) {}
