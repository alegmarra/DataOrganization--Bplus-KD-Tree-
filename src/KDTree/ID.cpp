/*
 * ID.cpp
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#include "ID.h"


void ID::addKey(Key key){

	keys.push_back(key);
}

std::vector<Key>* ID::getKeys(){
	return &keys;
}

unsigned ID::getSize(){
	return size;
}


ID::~ID() {
	// TODO Auto-generated destructor stub
}


