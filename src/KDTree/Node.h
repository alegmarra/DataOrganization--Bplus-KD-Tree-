#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "Serializers/Serializable.h"
//#include "Serializers/NodeSerializer.h"

#define LEVEL_MASK 0x7F

class Record;
class Key;
class PairKeyNode;


class Node : public Serializable {
public:
    Node();
	Node(unsigned _level);

	virtual unsigned getLevel();
	virtual unsigned getNumElements();

	virtual Node* split() = 0;

	virtual int insert(Record* record)=0;

	virtual Node* grow() =0;

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
