#ifndef INNER_NODE_H
#define INNER_NODE_H

#include "Node.h"

class PairKeyNode{

    private:
        Key* key;
        unsigned next;

    public:
        PairKeyNode();
        PairKeyNode(Key* _key, unsigned nextNodeNumber);

        Key* getKey();
        unsigned getNode();

        virtual ~PairKeyNode();
};

class InnerNode: public Node{

    public:
        InnerNode();
        InnerNode(unsigned _level);

        virtual Node* split();

    	virtual int insert(Record* record);

    	virtual Node* grow();

    	void addPair(PairKeyNode* pair);

//        virtual Node* getLeftChild();
//        virtual Node* getRightChild();
//
        virtual void setLeft(unsigned child);
//        virtual void setRight(Node* child);

        int serialize(char* buffer);
        int deserialize(const char* buffer);

        ~InnerNode();
        /** fea idea, pero es por falta de tiempo */
#ifdef TESTING
        friend class SerializersTest;
#endif
    private:
        unsigned firstLeft;
        std::vector<PairKeyNode*> elements;
};



#endif  // INNER_NODE_H
