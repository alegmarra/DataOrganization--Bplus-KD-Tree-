#include "KeyFactory.h"
#include "Linea.h"
#include "FranjaHoraria.h"
#include "Falla.h"
#include "Accidente.h"
#include "Formacion.h"

#include <stdlib.h>
#include <string>

unsigned KeyFactory::k = 5;

Key* KeyFactory::getKey(unsigned level) {
    if (k != 5)
        return new IntKey(8);
    else {
        switch (level % k) {
            case LINEA:     return new Linea();
            case FRANJA:    return new FranjaHoraria();
            case FALLA:     return new Falla();
            case ACCIDENTE: return new Accidente();
            case FORMACION: return new Formacion();
            default: return NULL;
        }
    }
}

Key* KeyFactory::getKey(unsigned level, std::string value)
{
   if (k != 5)
        return new IntKey(8, atoi(value.c_str()));
    else {
        switch (level % k) {
            case LINEA:     return new Linea(value);
            case FRANJA:    return new FranjaHoraria(atoi(value.c_str()));
            case FALLA:     return new Falla(value);
            case ACCIDENTE: return new Accidente(value);
            case FORMACION: return new Formacion(atoi(value.c_str()));
            default: return NULL;
        }
    }
}

void KeyFactory::setDimensions(unsigned _k) {
    k = _k;
}
