#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "../Serializers/Serializable.h"
#include "../Query/Query.h"
#include "../Record.h"
#define LEVEL_MASK 0x7F

class Key;
class PairKeyNode;


class Node : public Serializable {

public:
    Node();
	Node(unsigned _level);

	//Node overflow when exceeds 75% of fullSize
	static void setFullSize(unsigned size);


	virtual unsigned getLevel();
	virtual unsigned getNumElements();

	virtual int insert(Record* record)=0;
	virtual int remove(ID* id)=0;

	virtual Node* grow()=0;
	virtual Key* split(Node*& newNode)=0;

	virtual std::vector<Record*> find(Query* query)=0;
    
//    virtual int remove(ID* id) = 0;
//
	virtual ~Node();

    /** fea idea, pero es por falta de tiempo */
#ifdef TESTING
    friend class SerializersTest;
#endif

protected:
	unsigned level;
	unsigned numElements;
	unsigned occupiedSpace;
    static unsigned maxSize;


    unsigned getKeyByLevel(ID * id, unsigned level);

};


#endif /* NODO_H_ */

