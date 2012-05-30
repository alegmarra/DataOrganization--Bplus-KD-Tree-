#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include "Node.h"
#include "InnerNode.h"
#include "../Serializers/NodeSerializer.h"
#include "../Record.h"

#define IS_LEAF 0x80

class LeafNode: public Node{

public:
    LeafNode();
    LeafNode(unsigned _level);

    virtual int insert(Record* record);
    virtual std::vector<Record*> find(Query* query);

    virtual Key* split(Node* newNode);
    virtual Node* grow();

	int serialize(char* buffer);
	int deserialize(const char* buffer);

	~LeafNode();

private:

#ifdef TESTING
        friend class SerializersTest;
#endif

	virtual std::vector<Record*> find(Record* record);
	std::vector<Record*> sortBy(unsigned level);

	std::vector<Record*> elements;
};
#endif
