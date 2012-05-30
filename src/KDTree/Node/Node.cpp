#include "Node.h"

#ifndef MAX_SIZE
#define MAX_SIZE 3072
#endif

unsigned Node::maxSize = MAX_SIZE;

Node::Node() {
    level = 0;
    numElements = 0;
    occupiedSpace = 0;
}

Node::Node(unsigned _level) {
    level = _level;
    numElements = 0;
}

Node::~Node() {}

void Node::setFullSize(unsigned size){

	maxSize = (size * 0.75);
}

unsigned Node::getLevel() {
    return level;
}

unsigned Node::getNumElements() {
    return numElements;
}


unsigned getKeyByLevel(ID * id, unsigned level)
{
    return id->getKey(level % id->getDimensions());
}
