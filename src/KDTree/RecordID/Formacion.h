#ifndef FORMACION_H
#define FORMACION_H

#include "IntKey.h"

#define FORMACION 0

#include "IntKey.h"

class Formacion : public IntKey {
    public:
        Formacion();
        Formacion(int_least64_t value);
};

#endif  // FORMACION_H
