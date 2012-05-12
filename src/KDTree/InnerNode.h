#include "Node.h"

class InnerNode: public Node{

public:

	InnerNode(unsigned level);

	virtual int insert(Key* key, Node* next);

	virtual bool isLeaf();

	virtual Node* getLeftChild();
	virtual Node* getRightChild();

	virtual void setLeft(Node* child);
	virtual void setRight(Node* child);


	virtual ~InnerNode();

private:

	std::vector<PairKeyNode*> elements;


};
