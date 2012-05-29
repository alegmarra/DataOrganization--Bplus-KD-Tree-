#include "Node.h"

Node::Node() {
    level = 0;
    numElements = 0;
}

Node::Node(unsigned _level) {
    level = _level;
    numElements = 0;
}

Node::~Node() {}

unsigned Node::getLevel() {
    return level;
}

unsigned Node::getNumElements() {
    return numElements;
}
