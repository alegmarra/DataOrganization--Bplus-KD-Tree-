#include "LeafNode.h"


LeafNode::LeafNode() : Node() {}

LeafNode::LeafNode(unsigned _level) : Node(_level) {}

LeafNode::~LeafNode() {}


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

	//La hoja tiene sus records ordenados por key[level]
	//Size no deberia ser nunca 0, pues hay overflow
	Key* parentKey = elements.at((elements.size()/2) +1)->getID()->getKey(level);

	//New Leafs in next level
	//Half the elements in each
	this->level++;
	Node* newLeaf = this->split();

	//Assigns new number on serialization
	unsigned parentLeft = NodeSerializer::serializeNode(this);
	unsigned parentRight = NodeSerializer::serializeNode(newLeaf);


	newInner->setLeft(parentLeft);
	newInner->addPair(new PairKeyNode(parentKey, parentRight));

	return newInner;

}

/** @todo int LeafNode::insert(Record* ) */
int LeafNode::insert(Record* record) {

	//TODO
	return 1;
}

/** @todo Node* LeafNode::split() */
Node* LeafNode::split() {

	//TODO
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
