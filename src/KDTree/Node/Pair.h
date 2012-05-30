#ifndef PAIR_H_
#define PAIR_H_

#include <cstddef>

class Key;
class Node;

class PairKeyNode{

    private:
        Key* key;
        unsigned next;

    public:
        PairKeyNode();
        PairKeyNode(Key* _key, unsigned nextNodeNumber);

        Key* getKey();
        unsigned getNode();

        ~PairKeyNode();
};

#endif
