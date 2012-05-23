/*
 * ID.cpp
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#include "ID.h"


void ID::addKey(t_Key type, Key* key){

	keys->insert ( std::pair<t_Key, Key>(type, *key));
}

Key* ID::getKey(t_Key type){

	return & ((*(keys->find(type))).second);
}

unsigned ID::getSize(){
	return size;
}


ID::~ID() {
	// TODO Auto-generated destructor stub
}


