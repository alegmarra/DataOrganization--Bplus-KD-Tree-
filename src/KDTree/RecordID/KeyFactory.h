#ifndef KEY_FACTORY_H
#define KEY_FACTORY_H

class Key;

class KeyFactory {
    public:
        static void setDimensions(unsigned _k);
        static Key* getKey(unsigned level);
    private:
        static unsigned k;
};

#endif  // KEY_FACTORY_H
