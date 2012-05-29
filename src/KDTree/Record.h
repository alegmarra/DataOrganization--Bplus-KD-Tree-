/*
 * Record.h
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#ifndef RECORD_H_
#define RECORD_H_

#include "Serializers/Serializable.h"
#include "RecordID/ID.h"

class Record : public Serializable {

    public:
        Record();
        Record(ID* id);

        ID* getID();
    //	Data* getData();

        int serialize(char* buffer);
        int deserialize(const char* buffer);

        virtual ~Record();

private:
	ID* myID;
       // Data* data;


};

#endif /* RECORD_H_ */
