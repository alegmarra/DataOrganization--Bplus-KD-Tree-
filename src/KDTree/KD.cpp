/*
 * KD.cpp
 *
 *  Created on: Apr 29, 2012
 *      Author:
 */

#include "KD.h"

KDtree::KDtree(FileAbstract* myFile){

 treeFile = myFile;

 setRoot();

}

void KDtree::setRoot(){



}

void KDtree::insert(Record* record){

	this->insert(root, record);
}

int KDtree::insert(Node* node, Record* record){

	return 0;

}


KDtree::~KDtree() {

}
