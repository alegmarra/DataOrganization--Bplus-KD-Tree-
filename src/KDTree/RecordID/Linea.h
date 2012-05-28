#ifndef LINEA_H
#define LINEA_H

#include "StringKey.h"

#define LINEA 0

/** @todo clase ilustrativa, potencialmente eliminable */
class Linea : public StringKey {
    public:
        Linea() {}
        Linea(const std::string& s) : StringKey(s) {}
};

#endif  // LINEA_H
