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
#include "KDTree/Serializers/NodeSerializer.h"
#include "KDTree/Query/Query.h"
#include "../File/FileBlocks.h"


class Record;
class ID;
class Key;


class KDtree {
public:
	KDtree(FileAbstract* myFile);

	// TODO Carga los records de la lista
	void load(std::vector<Record*> records);

	//Inserta el record en el arbol, chequeando que no sea
	//una entrada duplicada
	int insert(Record* record);

	//TODO Si se encuentra, borra la entrada del arbol
	//Record* o ID* ¿?¿?
	void remove(Record* record);

	//TODO Busqueda punual de un record particular
	Record* find(Query* query);

	/*
	 * TODO
	 * Búsqueda parcial puntual.
	 * post: Devuelve todos los records que cumplan con el pedido parcial
	 */
	std::vector<Record> findAll(Query* query);

	/*
	 * TODO
	 * Busqueda por rangos.
	 *
	 * pre: Se pasa un vector con las Keys cuyo rango se desea verificar,
	 * en la forma (min - max).
	 * Las Keys no especificadas tienen rango 'infinito'
	 *
	 * post: devuelve todas los records con Keys dentro del rango.
	 */
	std::vector<Record> findInRange(std::vector<std::vector<Key*> > keys);

	virtual ~KDtree();

private:

	//Recovers first Node in File.
	void setRoot();

	FileAbstract* treeFile;
	Node* root;

};

#endif /* KD_H_ */
