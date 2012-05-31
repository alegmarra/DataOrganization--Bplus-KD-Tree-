/*
 * Record.cpp
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#include "Record.h"
#include "RecordID/ID.h"

#ifndef K
#define K 5
#endif

Record::Record() {
    myID = NULL;
}

Record::Record(ID* id) : myID(id) {}

ID* Record::getID() {
	return myID;
}

Record::~Record() {
	delete myID;
}

int Record::serialize(char* buffer) {
    return myID->serialize(buffer);
}

int Record::deserialize(const char* buffer) {
    if (!myID)
        myID = new ID(K);
    return myID->deserialize(buffer);
}

unsigned Record::size(){
	return myID->getSize();
}
