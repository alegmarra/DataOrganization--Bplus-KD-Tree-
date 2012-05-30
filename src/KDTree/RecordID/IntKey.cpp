#include "IntKey.h"
#include "../../Exceptions/InvalidIntSizeException.h"

#define MAX_BYTES 8

IntKey::IntKey(unsigned _size) {
    if (_size > MAX_BYTES || _size < 1 )
        throw InvalidIntSizeException(size);

    size = _size;
    value = 0;
}

IntKey::IntKey(int_least64_t _value, unsigned _size) {
    if (_size > MAX_BYTES || _size < 1 )
        throw InvalidIntSizeException(size);

    size = _size;
    value = _value;
}

int IntKey::compareTo(Key* k) {
    IntKey* ik = dynamic_cast<IntKey* >(k);
    if (!ik)
        throw InvalidKeyException("Invalid Type");

    return value - ik->value;
}

int IntKey::serialize(char* buffer) {
    for (unsigned i = 0; i < size; ++i)
        buffer[i] = value >> i*8;

    return size;
}

int IntKey::deserialize(const char* buffer) {
    for (unsigned i = 0; i < size; ++i)
        value = value | int_least64_t((unsigned char)buffer[i]) << i*8;

    // extensión del signo
    if (buffer[size-1] < 0)
        for (unsigned i = size; i < MAX_BYTES; ++i)
            value = value | int_least64_t(0xFF) << i*8;

    return size;
}

unsigned IntKey::getSize() {
    return size;
}

int_least64_t IntKey::getValue() {
    return value;
}
