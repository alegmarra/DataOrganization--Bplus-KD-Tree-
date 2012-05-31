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
    virtual std::vector<Record*> find(Query* query, unsigned dimension);
    virtual int remove(ID* id);

    virtual Key* split(Node*& newNode);
    virtual Node* grow();

    void dump();

	int serialize(char* buffer);
	int deserialize(const char* buffer);

	~LeafNode();


private:

#ifdef TESTING
        friend class SerializersTest;
        friend class NodeTest;
#endif

	virtual std::vector<Record*> find(Record* record);
	std::vector<Record*> sortBy(unsigned level);
	std::vector<Record*> elements;

    void init();


    int findLowLimit(Key* parentKey);



};
#endif
