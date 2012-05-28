#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include "Node.h"
#include "InnerNode.h"
#include "Serializers/NodeSerializer.h"
#include "Record.h"

#define IS_LEAF 0x80

class LeafNode: public Node{
    public:
        LeafNode();
        LeafNode(unsigned _level);


    	virtual Node* split();

    	virtual int insert(Record* record);
    	virtual Node* grow();

    //	virtual Node* nextLeaf();

        int serialize(char* buffer);
        int deserialize(const char* buffer);

        ~LeafNode();

        /** fea idea, pero es por falta de tiempo */
#ifdef TESTING
        friend class SerializersTest;
#endif
    private:
        std::vector<Record* > elements;
};
#endif
