#include "IntKey.h"
#include "../../Exceptions/InvalidIntSizeException.h"

IntKey::IntKey(unsigned _size) {
    if (_size > 8 || _size < 1 )
        throw InvalidIntSizeException(size);

    size = _size;
    value = 0;
}

IntKey::IntKey(int_least64_t _value, unsigned _size) {
    if (_size > 8 || _size < 1 )
        throw InvalidIntSizeException(size);

    size = _size;
    value = _value;
}

int IntKey::compareTo(Key* k) {
    IntKey* ik = dynamic_cast<IntKey* >(k);
    if (!ik)
        throw InvalidKeyException();

    return value - ik->value;
}

int IntKey::serialize(char* buffer) {
    for (unsigned i = 0; i < size; ++i)
        buffer[i] = uint_least64_t(value) >> i*8;

    return size;
}

int IntKey::deserialize(const char* buffer) {
    for (unsigned i = 0; i < size; ++i)
        value = value | int_least64_t(buffer[i]) << i*8;

    return size;
}
