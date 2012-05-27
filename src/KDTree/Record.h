/*
 * Record.h
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#ifndef RECORD_H_
#define RECORD_H_

#include "Serializers/Serializable.h"

class ID;

class Record : public Serializable {

    public:
        Record();
        Record(ID* id);

        ID* getID();
    //	Data* getData();

        int serialize(char* buffer);
        int deserialize(const char* buffer);

<<<<<<< HEAD
private:
	ID* myID;
       // Data* data;
=======
        virtual ~Record();

    private:
        ID* myID;
    //	Data* datos;
>>>>>>> 2b426eca9298f825aae6671da5bac6b96ba7440b
};

#endif /* RECORD_H_ */
