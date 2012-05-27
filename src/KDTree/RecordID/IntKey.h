#ifndef INT_KEY_H
#define INT_KEY_H

#include <inttypes.h>
#include "Key.h"

/** @todo considerar los unsigned */
class IntKey : public Key {
    public:
        /**
         * @brief constructor de una clave numérica, de entre 1 y 8 bytes
         * @throw InvalidIntSizeException
         */
        IntKey(unsigned _size);
        IntKey(int_least64_t _value, unsigned _size);
        int compareTo(Key* k);

        /* Serializable */
        int serialize(char* buffer);
        int deserialize(const char* buffer);
    private:
        int_least64_t value;
        unsigned size;
};

#endif  // INT_KEY_H
