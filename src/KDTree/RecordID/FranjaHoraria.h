#ifndef FRANJA_HORARIA_H
#define FRANJA_HORARIA_H

#define FRANJA 1

#include "IntKey.h"

class FranjaHoraria : public IntKey {
    public:
        FranjaHoraria();
        FranjaHoraria(int_least64_t value);
};

#endif  // FRANJA_HORARIA_H
