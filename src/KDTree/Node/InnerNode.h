#ifndef INNER_NODE_H
#define INNER_NODE_H

#include "Node.h"
#include "Pair.h"

class InnerNode: public Node{

    public:
        InnerNode();
        InnerNode(unsigned _level);

    	virtual int insert(Record* record);
    	virtual std::vector<Record*> find(Query* query);
        virtual int remove(ID* id);

    	void addPair(PairKeyNode* pair);

    	//TODO ambos tiran exception
    	virtual Node* grow();
    	virtual Key* split(Node* newNode);

        virtual void setLeft(unsigned child);

        int serialize(char* buffer);
        int deserialize(const char* buffer);

        ~InnerNode();

    private:

	#ifdef TESTING
			friend class SerializersTest;
	#endif

    	virtual std::vector<Record*> find(Record* record);

    	std::vector<Record*> findInRange(Query* query,
        					 std::vector<PairKeyNode*>::iterator it);

    	int manageOverflow(unsigned oldLeafNumber, Node* oldLeaf,
	 	 	 	  std::vector<PairKeyNode*>::iterator position);

        unsigned firstLeft;
        std::vector<PairKeyNode*> elements;


};


#endif  // INNER_NODE_H
