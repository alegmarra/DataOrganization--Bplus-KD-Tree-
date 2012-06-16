#include "KD.h"
#include "../Exceptions/FileErrorException.h"
#include "Node/LeafNode.h"


KDtree::KDtree(unsigned nDimensions, FileAbstract* myFile)
{
    dimensions = nDimensions;
    treeFile = myFile;
    setRoot();
}

/*
 * @brief	Remove the Record with @id
 *
 * @return	0 if removed
 * 			1 if not found
 */
int KDtree::remove(Record* record){

	int result = root->remove(record->getID());

	if (result == 0)
		NodeSerializer::serializeNode(root, 0);

	return result;

}

/*
 *@brief	Recovers root node in from file
 *			If empty tree (no root), creates one
 */
void KDtree::setRoot() {

	Record::setDimensions(dimensions);
  	NodeSerializer::setFile((FileBlocks *)treeFile);
    Node::setFullSize(((FileBlocks *)treeFile)->getBlockSize());

	try{

		root = NodeSerializer::deserializeNode(0);
	}
	catch(FileErrorException& e){
		root = new LeafNode();
		NodeSerializer::serializeNode(root);
	}

}

void KDtree::clear(){
	treeFile->deleteData();
	setRoot();
}

/*
 * @brief	Inserts record in tree
 *
 * @return	0 succesfull insertion
 * 			1 duplicated record
 */
int KDtree::load(std::vector<Record*>& records){
	std::vector<Record*>::iterator it;

	int returnStatus = 0;


	int partialStatus;
    int debugIt = 0;  // debuggin purposes only
	for(it = records.begin(); it < records.end(); it++, debugIt++){
		int partialStatus = root->insert(*it);

		if(partialStatus == 2){
			//root overflow
			root = root->grow();
		}
		else if (partialStatus == 3){
			//Duplicated record in load
			returnStatus = 1;
		}
	}

	NodeSerializer::serializeNode(root, 0);

	return returnStatus;
}


int KDtree::insert(Record* record){

	if(!dimensions){
		dimensions = record->getID()->getDimensions();
	}
	int result = root->insert(record);

	switch (result){
	//No update on root
	case 0: break;
	//root Updated
	case 1: NodeSerializer::serializeNode(root, 0);
		break;
	//root Overflow
	case 2:
		//Splits in two leafs and returns an inner node,
		//the new root.
		root = root->grow();
		NodeSerializer::serializeNode(root, 0);
		break;
	//Duplicated record
	case 3: return 1;
		break;
	};

	return 0;
}

std::vector< Record * > KDtree::find(Query* query)
{
    return root->find(query, dimensions);
}

void KDtree::dump()
{
    std::cout << std::endl;
    std::cout << "Node 0:";
    root->dump();
    std::cout << std::endl;

}


KDtree::~KDtree() {
	delete treeFile;
	delete root;
}
