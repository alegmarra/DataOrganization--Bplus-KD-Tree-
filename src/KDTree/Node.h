/*
 * Node.h
 *
 *  Created on: Apr 30, 2012
 *      Author: AleMarra
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "Serializers/Serializable.h"
//#include "Serializers/NodeSerializer.cpp"

#define LEVEL_MASK 0x7F

class Record;
class Key;
class PairKeyNode;
class NodeIterator; // REMOVE


class Node : public Serializable {
public:
    Node();
	Node(unsigned _level);

	virtual unsigned getLevel();
	virtual unsigned getNumElements();

	virtual Node* split() = 0;

	virtual int insert(Record* record)=0;

	virtual ~Node();

    /** fea idea, pero es por falta de tiempo */
#ifdef TESTING
    friend class SerializersTest;
#endif

protected:
	unsigned level;
	unsigned numElements;
};


#endif /* NODO_H_ */
