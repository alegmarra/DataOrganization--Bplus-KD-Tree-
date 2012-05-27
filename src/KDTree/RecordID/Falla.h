#ifndef FALLA_H
#define FALLA_H

#include "StringKey.h"

#define FALLA 2

/** @todo clase ilustrativa, potencialmente eliminable */
class Falla : public StringKey {
    public:
        Falla() {}
        Falla(const std::string& s) : StringKey(s) {}
};

#endif  // FALLA_H
