#include "LeafNode.h"

LeafNode::LeafNode() : Node() {}

LeafNode::LeafNode(unsigned _level) : Node(_level) {}

LeafNode::~LeafNode() {}

/** @todo int LeafNode::insert(Record* ) */
int LeafNode::insert(Record* record) {

}

/** @todo int LeafNode::split() */
Node* LeafNode::split() {

}

int LeafNode::serialize(char* buffer) {
    buffer[0] = IS_LEAF | level;
    buffer[1] = numElements;
    int bytes = 2;

    for (unsigned i = 0; i < numElements; ++i)
        bytes += elements[i]->serialize(buffer + bytes);

    return bytes;
}

int LeafNode::deserialize(const char* buffer) {
    level = LEVEL_MASK & buffer[0];
    numElements = buffer[1];
    elements.resize(numElements);
    int bytes = 2;
    Record aux;

    for (unsigned i = 0; i < numElements; ++i) {
        Record* aux = new Record;
        bytes += aux->deserialize(buffer + bytes);
        elements[i] = aux;
    }

    return bytes;
}
