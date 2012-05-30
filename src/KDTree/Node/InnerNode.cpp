#include "InnerNode.h"
#include <iostream>
#include "../RecordID/KeyFactory.h"
#include "../RecordID/Key.h"
#include "../../Exceptions/InvalidOperationException.cpp"
#include "../Serializers/NodeSerializer.h"

InnerNode::InnerNode() : Node() {}

InnerNode::InnerNode(unsigned _level) : Node(_level) {}

int InnerNode::insert(Record* record) {

	std::vector<PairKeyNode*>::iterator it = elements.begin();
	ID* id = record->getID();

	Key* inRecordKey = id->getKey(level % id->getDimensions());

	int result = inRecordKey->compareTo((*it)->getKey());

	while(it < elements.end()){

		if (result < 0){
			Node* next= NodeSerializer::deserializeNode(firstLeft);
			result = next->insert(record);
			if (result == 2)
				return manageOverflow(firstLeft, next, ++it);

			else return result;
		}
		else
		if(result == 0){
			Node* next = NodeSerializer::deserializeNode((*it)->getNode());
			result = next->insert(record);
			if (result == 2)
				return manageOverflow((*it)->getNode(), next, ++it);

			else return result;
		}
		it++;
	}

	//Key > all elements
	Node* next = NodeSerializer::deserializeNode((*it)->getNode());
	result = next->insert(record);
	if (result == 2)
		return manageOverflow((*it)->getNode(), next, ++it);

	else return result;
}

int InnerNode::manageOverflow(unsigned oldNumber, Node* oldLeaf,
			 	 	 	 	  std::vector<PairKeyNode*>::iterator position){

	if (occupiedSpace < maxSize){
		Node* newLeaf = NULL;

		Key* newKey = oldLeaf->split(newLeaf);
		NodeSerializer::serializeNode(oldLeaf, oldNumber);

		unsigned next;
		next = NodeSerializer::serializeNode(newLeaf);

		elements.insert(position, new PairKeyNode(newKey, next));
		return 1;
	}
	else
		NodeSerializer::serializeNode(oldLeaf->grow(), oldNumber);
	//No update in node
	return 0;

}

Node* InnerNode::grow() {
	throw InvalidOperationException("Called Grow for InnerNode");
}

Key* InnerNode::split(Node* n) {
	throw InvalidOperationException("Called Split for InnerNode");
}

void InnerNode::addPair(PairKeyNode* pair){

	std::vector<PairKeyNode*>::iterator it = elements.begin();
	bool added = false;

	int result =  pair->getKey()->compareTo((*it)->getKey());
	while((it < elements.end()) && (!added)){
		if( result >0)
			it++;
		else
		if( result == 0)
			throw InvalidKeyException("Duplicated Key in Node");
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

int InnerNode::remove(ID* id) {

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

