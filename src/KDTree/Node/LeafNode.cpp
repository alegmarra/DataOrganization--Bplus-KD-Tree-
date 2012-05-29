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
 *
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
	Node* newLeaf;
	Key* parentKey = this->split( newLeaf);

	//Assigns new number on serialization
	unsigned parentLeft = NodeSerializer::serializeNode(this);
	unsigned parentRight = NodeSerializer::serializeNode(newLeaf);


	newInner->setLeft(parentLeft);
	newInner->addPair(new PairKeyNode(parentKey, parentRight));

	return newInner;

}

/** @todo int LeafNode::insert(Record* ) */
int LeafNode::insert(Record* record) {


	return 1;
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
	Key* parentKey = elements.at((elements.size()/2) +1)->getID()->getKey(level);

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

Record* LeafNode::find(Query* query){

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

    return bytes;
}
