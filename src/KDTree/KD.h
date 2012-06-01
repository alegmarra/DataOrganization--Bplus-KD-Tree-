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
	KDtree(unsigned k, FileAbstract* myFile);

	/*
	 * @brief	Inserts all records in tree
	 *
	 * @return	0 succesfull insertion
	 * 			1 at least one duplicated record
	 * 			  was not inserted
	 */
	int load(std::vector<Record*>& records);


	/*
	 * @brief	Inserts record in tree
	 *
	 * @return	0 succesfull insertion
	 * 			1 duplicated record
	 */
	int insert(Record* record);


	/*
	 * @brief	Remove the Record with @id
	 *
	 * @return	0 if removed
	 * 			1 if not found
	 */
	int remove(Record* record);

	//TODO Busqueda punual de un record particular
	std::vector< Record * > find(Query* query);


	void clear();

    void dump();


	virtual ~KDtree();

private:

	//Recovers first Node in File.
	void setRoot();

	FileAbstract* treeFile;
	Node* root;
    unsigned dimensions;
};

#endif /* KD_H_ */
