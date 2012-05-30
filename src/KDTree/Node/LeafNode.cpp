#include "LeafNode.h"


LeafNode::LeafNode() : Node() {}

LeafNode::LeafNode(unsigned _level) : Node(_level) {}

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
 * */
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
	Key* parentKey = this->split( newLeaf);

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
int LeafNode::insert(Record* record) {

	if (find(record).size() != 0)
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
	if(!inserted) elements.push_back(record);

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

	for(unsigned i=0; i<level; i++)
		exactQ->addCondition(i, new QueryCondition(record->getID()->getKey(i)));

	return find(exactQ);
}

/**
 *
 * @brief recieves a query and searches for matching records
 *
 * @param query
 *
 * @return FIRST record that MATCHES
 *
 * @throw FileNotSetException, FileErrorException,
 * 		  InvalidOperationException
 */
std::vector<Record*> LeafNode::find(Query* query){

	std::vector<Record*>  matchingRecords;
	unsigned passed = 0;
	std::vector<Record*>::iterator it;

	//For every element in Node
	for (it = elements.begin(); it < elements.end(); it++){
		//For each Key that element has
		for(unsigned i= 0; i < query->size(); i++){

			Key* key = (*it)->getID()->getKey(i);
			//If the Key passes the condition
			if ((query->eval(i,key) == Query::EQUAL) ||
				(query->eval(i,key) == Query::MATCH))
				passed++;
		}
		//If every condition in the query passed
		if(passed == query->size())
			matchingRecords.push_back(*it);
	}

	return matchingRecords;
}


std::vector<Record*> LeafNode::sortBy(unsigned level) {

	std::vector<Record*>::iterator it = elements.begin();
	std::vector<Record*>::iterator parentIt;
	std::vector<Record*> parentKeySorted;
	for (; it < elements.end(); it++) {
		Key* key = (*it)->getID()->getKey(level - 1);
		for (parentIt = parentKeySorted.begin();
				parentIt < parentKeySorted.end(); parentIt++) {
			if (((*parentIt)->getID()->getKey(level - 1))->compareTo(key))
				parentKeySorted.insert(parentIt, *it);
		}
		if (parentIt == parentKeySorted.end())
			parentKeySorted.push_back(*it);
	}

	return parentKeySorted;
}

/*
 * Elements must be pre-ordered
 * Record that caused the overflow already
 * in Elements
 *
 * Instantiates a new leaf, passes to it the upper
 * half of its elements, and its level.
 *
 * returns new leaf in @newNode param
 *
 * returns middle key in return
 *
 * */
Key* LeafNode::split(Node* newNode) {

	newNode = new LeafNode(level);

	//Leaf has its records ordered by Key[level]
	Key* parentKey = sortBy(level-1).at((elements.size()/2) +1)->getID()->getKey(level-1);

	std::vector<Record*>::iterator it = elements.begin();
	int limit = (elements.size()/2);

	for (int i = 0; i<limit; i++)
		it++;

	for(; it<elements.end(); it++){
		//Pases element to new
		newNode->insert(*it);
		//removes element from this list
		elements.erase(it);
	}

	//Updates data
	numElements = limit;

	return parentKey;
}


int LeafNode::serialize(char* buffer) {
    buffer[0] = IS_LEAF | level;
    buffer[1] = numElements;
    int bytes = 2;

    for (unsigned i = 0; i < numElements; ++i)
        bytes += elements[i]->serialize(buffer + bytes);


    // TOOD me hace ruido, mepa que esta mal
    occupiedSpace = bytes;

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