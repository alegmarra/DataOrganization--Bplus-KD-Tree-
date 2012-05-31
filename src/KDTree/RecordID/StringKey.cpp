#include "StringKey.h"
#include <cstring>

StringKey::StringKey() {}

StringKey::StringKey(const char* s) {
    value = s;
}

StringKey::StringKey(const std::string& s) {
    value = s;
}

int StringKey::compareTo(Key* k) {
    StringKey* sk = dynamic_cast<StringKey* >(k);
    if (!sk)
        throw InvalidKeyException("Invalid Type");

    return value.compare(sk->value);
}

int StringKey::deserialize(const char* buffer) {
    value = buffer;
    return value.size()+1;
}


int StringKey::serialize(char* buffer) {
    strcpy(buffer, value.c_str());
    return value.size()+1;
}

unsigned StringKey::getSize() {
    return value.size()+1;
}

void StringKey::dump() {
    std::cout << value;
}
