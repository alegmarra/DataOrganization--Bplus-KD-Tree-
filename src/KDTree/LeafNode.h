#include "Node.h"

class LeafNode: public Node{

public:

	LeafNode(unsigned level, Node* next);

	virtual int insert(Record* record);

	virtual bool isLeaf();

	virtual Node* nextLeaf();

	virtual ~LeafNode();

private:

	std::vector<Record*> elements;

};
