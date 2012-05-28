#include "KeyFactory.h"
#include "Linea.h"
#include "FranjaHoraria.h"
#include "Falla.h"
#include "Accidente.h"
#include "Formacion.h"

unsigned KeyFactory::k = 5;

Key* KeyFactory::getKey(unsigned level) {
    switch (level % k) {
        case LINEA:     return new Linea();
        case FRANJA:    return new FranjaHoraria();
        case FALLA:     return new Falla();
        case ACCIDENTE: return new Accidente();
        case FORMACION: return new Formacion();
        default: return NULL;
    }
}

void KeyFactory::setDimensions(unsigned _k) {
    k = _k;
}
