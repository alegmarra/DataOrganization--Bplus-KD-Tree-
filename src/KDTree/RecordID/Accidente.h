#ifndef ACCIDENTE_H
#define ACCIDENTE_H

#include "StringKey.h"

#define ACCIDENTE 3

/** @todo clase ilustrativa, potencialmente eliminable */
class Accidente : public StringKey {
    public:
        Accidente() {}
        Accidente(const std::string& s) : StringKey(s) {}
};

#endif  // ACCIDENTE_H
