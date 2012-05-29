#include "InnerNode.h"
#include <iostream>
#include "../RecordID/KeyFactory.h"
#include "../RecordID/Key.h"
#include "Exceptions/InvalidOperationException.cpp"
#include "../Serializers/NodeSerializer.h"

InnerNode::InnerNode() : Node() {}

InnerNode::InnerNode(unsigned _level) : Node(_level) {}

/** @todo int InnerNode::insert(Record* ) */
int InnerNode::insert(Record* record) {

	if (find(record).size() != 0)
			return 3;

	std::vector<PairKeyNode*>::iterator it = elements.begin();

	Key* inRecordKey = record->getID()->getKey(level);




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

std::vector<Record*> InnerNode::findInRange(Query* query,
					std::vector<PairKeyNode*>::iterator it) {

	std::vector<Record*> found;
	found = NodeSerializer::deserializeNode(firstLeft)->find(query);

	while ((query->eval(level, (*it)->getKey()) == Query::MATCH)
			&& (it < elements.end())) {

		std::vector<Record*> partial;
		partial = NodeSerializer::deserializeNode((*it)->getNode())->find(
				query);
		found.insert(found.end(), partial.begin(), partial.end());
		it++;
	}
	return found;
}

std::vector<Record*> InnerNode::find(Record* record){

	//Generates an exact query, wich has
	//an exact condition for every key in record
	Query* exactQ = new Query();

	for(unsigned i=0; i<level; i++)
		exactQ->addCondition(i, new QueryCondition(record->getID()->getKey(i)));

	return find(exactQ);
}

std::vector<Record*> InnerNode::find(Query* query){

	std::vector<Record*>  found;
	std::vector<PairKeyNode*>::iterator it;

	it=elements.begin();

	switch (query->eval(level, (*it)->getKey())){

		case (Query::LOWER):
			return NodeSerializer::deserializeNode(firstLeft)->find(query);

		case (Query::EQUAL):
			return NodeSerializer::deserializeNode((*it)->getNode())->find(query);

		case (Query::HIGHER):{
			unsigned prev ;

			while((query->eval(level, (*it)->getKey()) == Query::HIGHER)
				 && (it < elements.end())){
				 prev = (*it)->getNode();
				 it++;
			}
			if (it != elements.end())
				if(query->eval(level, (*it)->getKey()) == Query::MATCH)
					return findInRange(query, it);
				else
					return NodeSerializer::deserializeNode(prev)->find(query);
			else
				return NodeSerializer::deserializeNode((*it)->getNode())->find(query);
		}

		case (Query::MATCH):
			return findInRange(query, it);
	}

	return found; //Empty vector, nothing found
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

