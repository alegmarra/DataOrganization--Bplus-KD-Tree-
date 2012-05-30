/*
 * KD.h
 *
 *  Created on: Apr 29, 2012
 *      Author:
 */

#ifndef KD_H_
#define KD_H_
#include<iostream>
#include<fstream>
#include "Serializers/NodeSerializer.h"
#include "Query/Query.h"
#include "../File/FileBlocks.h"


class Record;
class ID;
class Key;


class KDtree {
public:
	KDtree(FileAbstract* myFile);

	void load(std::vector<Record*> records);

	//Inserta el record en el arbol, chequeando que no sea
	//una entrada duplicada
	int insert(Record* record);


	int remove(ID* id);

	//TODO Busqueda punual de un record particular
	std::vector<Record*> find(Query* query);

	virtual ~KDtree();

private:

	//Recovers first Node in File.
	void setRoot();

	FileAbstract* treeFile;
	Node* root;

};

#endif /* KD_H_ */
