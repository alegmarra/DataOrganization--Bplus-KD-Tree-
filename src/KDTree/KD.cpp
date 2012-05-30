/*
 * KD.cpp
 *
 *  Created on: Apr 29, 2012
 *      Author:
 */

#include "KD.h"
#include "../Exceptions/FileErrorException.h"
#include "Node/LeafNode.h"

KDtree::KDtree(FileAbstract* myFile){

 treeFile = myFile;

 setRoot();

}

void KDtree::setRoot(){

  	NodeSerializer::setFile((FileBlocks*)treeFile);

	try{
		root = NodeSerializer::deserializeNode(0);
	}
	catch(FileErrorException& e){
		root= new LeafNode();
		std::cout << NodeSerializer::serializeNode(root) <<std::endl;
	}

}

void KDtree::load(std::vector<Record*> records){
	std::vector<Record*>::iterator it;

	int status;

	for(it= records.begin(); it < records.end(); it++){
		status = root->insert(*it);
		if(status == 2)
			root = root->grow();
	}

	NodeSerializer::serializeNode(root, 0);
}


int KDtree::insert(Record* record){

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
	case 3: return 3;
		break;
	};

	return 1;
}

int KDtree::remove(ID* id){

	return root->remove(id);
}

KDtree::~KDtree() {
	delete treeFile;
	delete root;
}
