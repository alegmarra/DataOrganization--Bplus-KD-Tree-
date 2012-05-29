#ifndef INNER_NODE_H
#define INNER_NODE_H

#include "Node.h"
#include "Pair.h"

class InnerNode: public Node{

    public:
        InnerNode();
        InnerNode(unsigned _level);

    	virtual int insert(Record* record);
    	virtual Record* find(Query* query);

    	void addPair(PairKeyNode* pair);
    	virtual Node* grow();
        virtual void setLeft(unsigned child);

//        virtual Node* getLeftChild();
//        virtual Node* getRightChild();
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
