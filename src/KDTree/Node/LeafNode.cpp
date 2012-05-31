#include "LeafNode.h"
#include <iostream>


LeafNode::LeafNode() : Node() {
    init();
}

LeafNode::LeafNode(unsigned _level) : Node(_level) {
    init();
}

void LeafNode::init() {
    occupiedSpace = 2;  // level + numElements
}

LeafNode::~LeafNode() {}



/*
 * Elements must be pre-ordered
 * Record that caused the overflow already
 * in Elements
 *
 * Instantiates new Leaf, passes to it the upper
 * half of its elements, and its level.
 * Instantiates new Inner, inserts in it the middle key
 * and left and right childs
 *
 * Saves Leaf nodes on disk
 *td::vector<Record*
 * return Inner node
 *
 */

Node* LeafNode::grow() {

	/*
	 * Ya tiene agregado en elements el record que causo el overflow
	 * ordenado por la key levelActual
	 *
	 * instancia 2 nuevos nodos, uno interno otro hoja
	 * a la hoja le pasa la mitad mayor de su contenido
	 * al interno le pasa el promedio por la key levelActual de
	 * todos los registros
	 */

	InnerNode* newInner = new InnerNode(level);

	//New Leafs in next level
	//Half the elements in each
	this->level++;
	Node* newLeaf = NULL;
	Key* parentKey = this->split(newLeaf);

	//Assigns new number on serialization
	unsigned parentLeft = NodeSerializer::serializeNode(this);
	unsigned parentRight = NodeSerializer::serializeNode(newLeaf);

	newInner->setLeft(parentLeft);
	newInner->addPair(new PairKeyNode(parentKey, parentRight));

	return newInner;

}

/**
 * @brief recieves a record and adds it to elements
 * @param record        record to be added
 *
 * @return 1  Record inserted
 * 		   2  Overflow
 * 		   3  Record already exists
 *
 * @throw FileNotSetException, FileErrorException,
 * 		  InvalidOperationException
 */
#include <iostream>
#include "../RecordID/IntKey.h"

int LeafNode::insert(Record* record) {

ID* id = record->getID();
IntKey * x = dynamic_cast<IntKey *>(id->getKey(0));
IntKey * y = dynamic_cast<IntKey *>(id->getKey(1));
IntKey * z = dynamic_cast<IntKey *>(id->getKey(2));
//std::cout << "EnLeaf - ID: " << x->getValue() << " " << y->getValue() << " " << z->getValue() << std::endl;

    std::vector< Record * > result = find(record);

	if (result.size() != 0)
		return 3;

	//Key in level in inserted record ID
	Key* inRecordKey = record->getID()->getKey(level);

	bool inserted = false;
	std::vector<Record*>::iterator it = elements.begin();

	while((it < elements.end()) && (!inserted)){

		Key* elemKey = (*it)->getID()->getKey(level);

		if(inRecordKey->compareTo(elemKey) < 0){
			elements.insert(it, record);
			numElements++;
			inserted = true;
		}
		else
			it++;
	}

	if(!inserted) {
	    elements.push_back(record);
	    numElements++;
	}

	occupiedSpace += record->size();

	//Checks for overflow
	if (occupiedSpace > maxSize){
		return 2;
	}

	return 1;
}


/*
 * Private
 */
std::vector<Record*> LeafNode::find(Record* record){


	//Generates an exact query, wich has
	//an exact condition for every key in record
	Query* exactQ = new Query();

	for(unsigned i = 0; i < record->getID()->getDimensions(); i++) {
		exactQ->addCondition(i, new QueryCondition(record->getID()->getKey(i)));
    }

	std::vector< Record * > result = find(exactQ, record->getID()->getDimensions());
    // TODO Copiar la clave para poder borrar la query safely
	//delete exactQ;
	return result;
}

/**
 *
 * @brief recieves a query and searches for matching records
 *
 * @param query
 *
 * @return ALL records that matches every condition in query
 *
 * @throw FileNotSetException, FileErrorException,
 * 		  InvalidOperationException
 */
std::vector<Record*> LeafNode::find(Query* query, unsigned dimensions){

	std::vector<Record*>  matchingRecords;
	unsigned passed = 0;
	std::vector<Record*>::iterator it;
    int queryResult;

	//For every element in Node
	for (it = elements.begin(); it < elements.end(); it++) {
	    passed = 0;

		//For each Key that element has
		for(unsigned i = 0; i < dimensions; i++){

			Key* key = (*it)->getID()->getKey(i);
			//If the Key passes the condition

			queryResult = query->eval(i, key);

			if ((queryResult == Query::EQUAL) || (queryResult == Query::MATCH)) {
				passed++;
			}
			else break;
		}

		//If every condition in the query passed
		if(passed == dimensions)
			matchingRecords.push_back(*it);
	}

	return matchingRecords;
}



/*
 * @brief	Remove the Record with @id
 *
 * @return	0 if removed
 * 			1 if not found
 */
int LeafNode::remove(ID* id){

	std::vector<Record*>::iterator it;

	for(it = elements.begin(); it < elements.end(); it++)
		if( id->equalsTo((*it)->getID())){
			elements.erase(it);
			numElements--;
			return 0;
	}

	return 1;
}


/*
 * Sorts elements by Key corresponding to level%dimensions
 */
std::vector<Record*> LeafNode::sortBy(unsigned level)

{
    std::vector<Record*>::iterator it;
	std::vector<Record*>::iterator parentIt;
	std::vector<Record*> parentKeySorted;

	for (it = elements.begin(); it < elements.end(); it++) {

		Key* key = getKeyByLevel((*it)->getID(), level);

		for (parentIt = parentKeySorted.begin(); parentIt < parentKeySorted.end(); parentIt++) {
			if (getKeyByLevel((*parentIt)->getID(), level)->compareTo(key) > 0) {
				parentIt = parentKeySorted.insert(parentIt, *it);
				break;
			}
		}

		if (parentIt == parentKeySorted.end()) {
			parentKeySorted.push_back(*it);
		}
	}

	return parentKeySorted;
}



/*
 * Iterates over elements in order to find the best
 * split pivot.
 * Has big impact in the way the tree keeps balance.
 */
int LeafNode::findLowLimit(Key* parentKey){

	int lowLimit = 0;//=1
	int halfLimit = (elements.size()/2);
	int highLimit = (elements.size());

	//Searches for the first element wich key is lower than parent key
	while((lowLimit < (highLimit -1)) &&
		  (getKeyByLevel(elements.at(lowLimit)->getID(), level-1)->compareTo(parentKey) < 0)){

		//Element[i], lower than parent key, stays in this leaf
		lowLimit++;
	}

	if (lowLimit == 0){
		//First element key equals parentkey
		//Splits in a more balanced way
		while((lowLimit < halfLimit) &&
			  (getKeyByLevel(elements.at(lowLimit)->getID(), level-1)->compareTo(parentKey) <= 0)){

			//Element[i], lower than parent key, stays in this leaf
			lowLimit++;
		}
	}

	return lowLimit;

}


/*
 * @pre	Record that caused the overflow already in elements
 *
 * @brief	Instantiates a new leaf, passes to it the upper
 * 			part of its elements, and its level.
 *
 * @return	new leaf in @newNode param
 *
 * @return	middle key in return
 *
 */
Key* LeafNode::split(Node*& newNode) {

	newNode = new LeafNode(level);

	//Leaf has its records ordered by Key[level%dimension]
	elements = sortBy(level-1);

	int halfLimit = (elements.size()/2);

	Key * parentKey = getKeyByLevel(elements.at(halfLimit)->getID(), level-1);

	int lowLimit = 0;
	int highLimit = (elements.size());

	//finds the best split pivot.
	lowLimit = findLowLimit(parentKey);

	//Passes every element with key equal or higher than parent key to newLeaf
	for(int i = lowLimit; i< highLimit; i++) {
		newNode->insert(elements[i]);
	}

	//Updates space and elements in this leaf
	for(int i = lowLimit; i< highLimit; i++){
		occupiedSpace -= elements[lowLimit]->size();
		elements.erase(elements.begin() + lowLimit);
	}

	//Updates data
	numElements = lowLimit;

	return parentKey;
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

    for (unsigned i = 0; i < numElements; ++i) {
        Record* aux = new Record;
        bytes += aux->deserialize(buffer + bytes);
        elements[i] = aux;
    }

    occupiedSpace = bytes;

    return bytes;
}

void LeafNode::dump()
{
    std::cout << level << "|";

    for (int i = 0; i < elements.size(); i++) {
        elements[i]->dump();
    }
}
