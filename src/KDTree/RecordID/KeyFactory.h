#ifndef KEY_FACTORY_H
#define KEY_FACTORY_H

#include <string>

class Key;

class KeyFactory {
    public:
        static void setDimensions(unsigned _k);
        static Key* getKey(unsigned level);
        static Key* getKey(unsigned level, std::string value);
    private:
        static unsigned k;
};

#endif  // KEY_FACTORY_H
