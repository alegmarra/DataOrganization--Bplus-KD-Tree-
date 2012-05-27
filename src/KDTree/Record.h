/*
 * Record.h
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#ifndef RECORD_H_
#define RECORD_H_

#include "ID.h"

class Record {

public:
	Record(ID* id): myID(id){};

	ID* getID();


	virtual ~Record();

private:
	ID* myID;
       // Data* data;
};

#endif /* RECORD_H_ */
