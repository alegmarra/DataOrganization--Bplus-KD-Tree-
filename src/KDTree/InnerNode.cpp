#include "InnerNode.h"
#include <iostream>
#include "RecordID/KeyFactory.h"
#include "RecordID/Key.h"

InnerNode::InnerNode() : Node() {}

InnerNode::InnerNode(unsigned _level) : Node(_level) {}

/** @todo int InnerNode::insert(Record* ) */
int InnerNode::insert(Record* record) {

}

/** @todo int InnerNode::split() */
Node* InnerNode::split() {

}

int InnerNode::serialize(char* buffer) {
    buffer[0] = level;
    buffer[1] = numElements;
    buffer[2] = firstLeft;
    int bytes = 3;

    for (unsigned i = 0; i < numElements; ++i) {
        bytes += elements[i].getKey()->serialize(buffer + bytes);
        buffer[bytes++] = elements[i].getNode();
    }

    return bytes;
}

int InnerNode::deserialize(const char* buffer) {
    level = LEVEL_MASK & buffer[0];
    numElements = buffer[1];
    elements.resize(numElements);
    firstLeft = buffer[2];
    int bytes = 3;
    unsigned next;

    for (unsigned i = 0; i < numElements; ++i) {
        Key* key = KeyFactory::getKey(level);
        bytes += key->deserialize(buffer + bytes);
        next = buffer[bytes++];
        elements[i] = PairKeyNode(key, next);
    }

    return bytes;
}

InnerNode::~InnerNode() {}

PairKeyNode::PairKeyNode() {
    key = NULL;
    next = 0;
}

PairKeyNode::PairKeyNode(Key* _key, unsigned nextNodeNumber) {
    key = _key;
    next = nextNodeNumber;
}

Key* PairKeyNode::getKey() {
    return key;
}

unsigned PairKeyNode::getNode() {
    return next;
}
