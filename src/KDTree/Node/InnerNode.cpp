#include "InnerNode.h"
#include "../RecordID/KeyFactory.h"
#include "../RecordID/Key.h"
#include "../../Exceptions/InvalidOperationException.cpp"
#include "../Serializers/NodeSerializer.h"
#include <iostream>

InnerNode::InnerNode() : Node() {}

InnerNode::InnerNode(unsigned _level) : Node(_level) {
    occupiedSpace = 2;
}

int InnerNode::insert(Record* record) {

	std::vector<PairKeyNode*>::iterator it = elements.begin();
	ID* id = record->getID();

	Key* inRecordKey = getKeyByLevel(id, level);
    int result;

    // First check if the left node should handle the shit
    if(inRecordKey->compareTo((*it)->getKey()) < 0) {
        Node* next = NodeSerializer::deserializeNode(firstLeft);
		result = next->insert(record);

		if (result == 2) {
			return manageOverflow(firstLeft, next, it);
		} else if (result == 1) {
	        NodeSerializer::serializeNode(next, firstLeft);
	    }

        return result;
    }

	while(it < elements.end()) {

	    result = inRecordKey->compareTo((*it)->getKey());

        // TODO Limpiar

		if (result < 0) {
            it--;
            unsigned nextNum = (*it)->getNode();
			Node* next = NodeSerializer::deserializeNode(nextNum);
			result = next->insert(record);
            it++;

			if (result == 2) {
				return manageOverflow(nextNum, next, it);
			} else if (result == 1) {
		        NodeSerializer::serializeNode(next, nextNum);
		    }

	        return result;

		} else if(result == 0) {
			Node* next = NodeSerializer::deserializeNode((*it)->getNode());
			result = next->insert(record);
			if (result == 2) {

				return manageOverflow((*it)->getNode(), next, it + 1);
			} else {
			    if (result == 1) {
			        NodeSerializer::serializeNode(next, (*it)->getNode());
			        return result;
		        }
		    }
		} else {
		    // Handled below
		}

		it++;
	}

	//Key > all elements
	if (it == elements.end()) {
	    it -= 1;
	}


	Node* next = NodeSerializer::deserializeNode((*it)->getNode());
	result = next->insert(record);
	if (result == 2) {
		return manageOverflow((*it)->getNode(), next, it + 1);
    } else if (result == 1) {
        NodeSerializer::serializeNode(next, (*it)->getNode());
    }

    return result;

}

int InnerNode::manageOverflow(unsigned oldNumber, Node* oldLeaf,
			 	 	 	 	  std::vector<PairKeyNode*>::iterator position){

/*
	if((*position)->getKey()->compareTo((*(position-1))->getKey()) == 0){

		Node* next = NodeSerializer::deserializeNode((*position)->getNode());
		int result = next->insert( );
	}
*/


	if (occupiedSpace < maxSize){
		Node* newLeaf = NULL;

		Key* newKey = oldLeaf->split(newLeaf);

		NodeSerializer::serializeNode(oldLeaf, oldNumber);
		unsigned next;
		next = NodeSerializer::serializeNode(newLeaf);

		PairKeyNode* pair = new PairKeyNode(newKey, next);

		elements.insert(position, pair);


		occupiedSpace += pair->getSize();

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

Key* InnerNode::split(Node*& n) {
	throw InvalidOperationException("Called Split for InnerNode");
}

void InnerNode::addPair(PairKeyNode* pair){

	std::vector<PairKeyNode*>::iterator it = elements.begin();
	bool added = false;
	int result;

	while((it < elements.end()) && (!added)){
        result = pair->getKey()->compareTo((*it)->getKey());
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

    numElements++;
}



std::vector<Record*> InnerNode::findByCondition(unsigned prevNode, Query* query,
					std::vector<PairKeyNode*>::iterator it, unsigned qCondition , unsigned dimensions) {

	std::vector<Record*> found;
	if (prevNode){


		//std::cout << "PREV NODE " << prevNode<< std::endl;



		found = NodeSerializer::deserializeNode(prevNode)->find(query, dimensions);
	}

	while ( (it < elements.end() && (query->eval(level, (*it)->getKey()) == qCondition))) {

		std::vector<Record*> partial;


		//std::cout << "GET NODE " << (*it)->getNode()<< std::endl;

		partial = NodeSerializer::deserializeNode((*it)->getNode())->find(query, dimensions);
		found.insert(found.end(), partial.begin(), partial.end());
		it++;
	}
	return found;
}

/*
std::vector<Record*> InnerNode::findInRange(unsigned prevNode, Query* query,
					std::vector<PairKeyNode*>::iterator it) {

	std::vector<Record*> found;
	found = NodeSerializer::deserializeNode(prevNode)->find(query);

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
*/


std::vector<Record*> InnerNode::find(Record* record){

	//Generates an exact query, wich has
	//an exact condition for every key in record
	Query* exactQ = new Query();

	for(unsigned i=0; i<level; i++)
		exactQ->addCondition(i, new QueryCondition(record->getID()->getKey(i)));

	return find(exactQ, record->getID()->getDimensions());
}




//TODO multiple search por equal
//Keys reales
//TODO intentar hacer mierda el àrbol con muchos registros y las claves reales del TP

#include "../RecordID/IntKey.h"

std::vector<Record*> InnerNode::find(Query* query, unsigned dimensions){

	std::vector<Record*>  found;
	std::vector<PairKeyNode*>::iterator it;

	it=elements.begin();

//	std::cout << "IT KEY " <<(dynamic_cast<IntKey*>((*it)->getKey()))->getValue() <<std::endl;
	//std::cout << "DIMENSION " << (level%dimensions) <<std::endl;
	switch (query->eval((level%dimensions), (*it)->getKey())){

		case (Query::HIGHER):{

		//	std::cout << "HIGHER " << firstLeft<< std::endl;

 			return NodeSerializer::deserializeNode(firstLeft)->find(query, dimensions);
		}
		case (Query::EQUAL):{

			//std::cout << "EQUAL " << firstLeft<< std::endl;

/*
			std::vector<Record*> partial;

			while((query->eval(level, (*it)->getKey()) == Query::EQUAL)
					 && (it < elements.end())){

				partial = NodeSerializer::deserializeNode((*it)->getNode())->find(query);
				found.insert(found.end(), partial.begin(), partial.end());
				it++;
			}
			return found;
*/
			return findByCondition(firstLeft, query, it,Query::EQUAL, dimensions);
		}

		case (Query::LOWER):{

			//std::cout << "LOWER" << std::endl;

			unsigned prev ;

			while((it < elements.end()) && (query->eval(level, (*it)->getKey()) == Query::LOWER)){
					 prev = (*it)->getNode();
					 it++;
			}
			if (it != elements.end()){

				if(query->eval(level, (*it)->getKey()) == Query::MATCH)
					//return findInRange(prev, query, it);
					return findByCondition(prev, query, it,Query::MATCH, dimensions);

				else{
					return NodeSerializer::deserializeNode((*it)->getNode())->find(query, dimensions);
				}
			}
			else
				return NodeSerializer::deserializeNode((*(it-1))->getNode())->find(query, dimensions);
		}

		case (Query::MATCH):{
	//		std::cout << "MATCH" << std::endl;
			//return findInRange(firstLeft, query, it);
			return findByCondition(firstLeft, query, it,Query::MATCH, dimensions);
		}

	}

	return found; //Empty vector, nothing found
}


/*
 * @brief	Remove the Record with @id
 *
 * @return	0 if removed
 * 			1 if not found
 */
int InnerNode::remove(ID* id){

	std::vector<PairKeyNode*>::iterator it = elements.begin();

	unsigned dimension = id->getDimensions();

	while(it < elements.end()){
		if ((*it)->getKey()->compareTo(id->getKey(level%dimension)) == 0 ){

			int status = NodeSerializer::deserializeNode((*it)->getNode())->remove(id);

			if( status == 0 )
				return 0;
		}
	}

	return  1;

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
    firstLeft = (unsigned char)buffer[2];
    int bytes = 3;
    unsigned next;

    for (unsigned i = 0; i < numElements; ++i) {
        Key* key = KeyFactory::getKey(level);
        bytes += key->deserialize(buffer + bytes);
        next = (unsigned char)buffer[bytes++];
        elements[i] = new PairKeyNode(key, next);
    }

    return bytes;
}

void InnerNode::dump()
{
    std::cout << level << "|" << firstLeft;

    for (int i = 0; i < elements.size(); i++) {
        elements[i]->dump();
    }

    std::cout << std::endl;
    std::cout << "Node " << firstLeft << ":";
    NodeSerializer::deserializeNode(firstLeft)->dump();
    std::cout << std::endl;

    for (int i = 0; i < elements.size(); i++) {
        std::cout << "Node " << elements[i]->getNode() << ":";
        NodeSerializer::deserializeNode(elements[i]->getNode())->dump();
        std::cout << std::endl;
    }
}

InnerNode::~InnerNode() {}
