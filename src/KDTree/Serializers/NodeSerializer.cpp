/*
 *
 *
 #include "KDTree/Node.h"
class FileAbstract;

class NodeSerializer{
public:

	static void serialize(Node* node, FileAbstract* onFile){


		if (node->isLeaf())
			serializeLeaf(node, onFile);
		else
			serializeInner(node, onFile);


	}

	static Node* deSerialize(unsigned identifier, FileAbstract* onFile){

	}

private:

	static void serializeInner(Node* node, FileAbstract* onFile){
		if (node->isRoot()) {
			Block * b = onFile->find(0);
		}

		//Magia que guarda
	}

	static void serializeLeaf(Node* node, FileAbstract* onFile){

		if (node->alreadyExists()) {
			Block * b = onFile->find(node->getNum());
		} else {
			Block * b = onFile->fetchFreeBlock();
			node->setNum(b->getNum());
		}

		//Magia que guarda

	}



};
*/
