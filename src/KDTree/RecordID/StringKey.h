#ifndef STRING_KEY_H
#define STRING_KEY_H

#include "Key.h"

#include <iostream>

class StringKey : public Key {
    public:
        StringKey();
        StringKey(const char* s);
        StringKey(const std::string& s);
        int compareTo(Key* k);

        /* Serializable */
        int serialize(char* buffer);
        int deserialize(const char* buffer);

        unsigned getSize();
        std::string getValue();
        virtual void dump();
    private:
        std::string value;
};

#endif  // STRING_KEY_H

