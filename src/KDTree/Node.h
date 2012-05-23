/*
 * Node.h
 *
 *  Created on: Apr 30, 2012
 *      Author: AleMarra
 */

#ifndef NODE_H_
#define NODE_H_

#include<vector>
//#include "Serializers/NodeSerializer.cpp"

class Record;
class Key;
class PairKeyNode;
class NodeIterator; // REMOVE


class Node {
public:

	Node();

	static Node* create(unsigned level, unsigned number);

	virtual unsigned getLevel();
	virtual unsigned getNumElements();
	virtual unsigned getNodeNumber();

	virtual std::vector<void*> split();

	virtual bool isLeaf() =0;

	// for LeafNodes
	virtual int insert(Record* record)=0;

	// for InnerNodes
	virtual int insert(Key* key, Node* next)=0;


	virtual ~Node();

private:

	unsigned level;
	unsigned numElements;
	unsigned nodeNumber;

};

class PairKeyNode{

private:

	Key* key;
	Node* node;

public:
	PairKeyNode(Key* key, unsigned nextNodeNumber);

	Key* getKey();
	unsigned getNode();

};

#endif /* NODO_H_ */
