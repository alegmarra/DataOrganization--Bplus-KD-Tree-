#include "InnerNode.h"
#include <iostream>
#include "../RecordID/KeyFactory.h"
#include "../RecordID/Key.h"
#include "Exceptions/InvalidOperationException.cpp"

InnerNode::InnerNode() : Node() {}

InnerNode::InnerNode(unsigned _level) : Node(_level) {}

/** @todo int InnerNode::insert(Record* ) */
int InnerNode::insert(Record* record) {

	return 1;
}

Node* InnerNode::grow() {

	throw InvalidOperationException("Called Grow for InnerNode");

}

void InnerNode::addPair(PairKeyNode* pair){

	std::vector<PairKeyNode*>::iterator it = elements.begin();
	bool added = false;

	while((it < elements.end()) && (!added)){
		if( pair > *it )
			it++;
		else{
			elements.insert(it, pair);
			added = true;
		}
	}
	if (!added)
		elements.push_back(pair);

}

std::vector<Record*> InnerNode::find(Query* query){

}


void InnerNode::setLeft(unsigned child){
	firstLeft = child;
}

int InnerNode::serialize(char* buffer) {
    buffer[0] = level;
    buffer[1] = numElements;
    buffer[2] = firstLeft;
    int bytes = 3;

    for (unsigned i = 0; i < numElements; ++i) {
        bytes += elements[i]->getKey()->serialize(buffer + bytes);
        buffer[bytes++] = elements[i]->getNode();
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
        elements[i] = new PairKeyNode(key, next);
    }

    return bytes;
}

InnerNode::~InnerNode() {}

