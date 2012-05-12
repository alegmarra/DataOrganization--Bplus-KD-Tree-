/*
 * Record.cpp
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#include "Record.h"


ID* Record::getID(){
	return myID;
}

Record::~Record() {
	delete myID;
	// TODO Auto-generated destructor stub
}
