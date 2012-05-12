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
#include "Node.h"
#include "Serializers/KDtreeSerializer.cpp"

class Record;
class ID;
class Key;
class FileAbstract;

class KDtree {
public:
	KDtree(FileAbstract* myFile);

	//Carga los records de la lista, sin chequear unicidad
	void load(std::vector<Record*> records);

	//Inserta el record en el arbol, chequeando que no sea
	//una entrada duplicada
	void insert(Record* record);

	//Si se encuentra, borra la entrada del arbol
	void remove(Record* record);

	//Busqueda punual de un record particular
	Record search(ID* id);

	/*
	 * Búsqueda parcial puntual.
	 * post: Devuelve todos los records que cumplan con el pedido parcial
	 */
	std::vector<Record> searchAll(std::vector<Key*> key);

	/*
	 * Busqueda por rangos.
	 *
	 * pre: Se pasa un vector con las Keys cuyo rango se desea verificar,
	 * en la forma (min - max).
	 * Las Keys no especificadas tienen rango 'infinito'
	 *
	 * post: devuelve todas los records con Keys dentro del rango.
	 */
	std::vector<Record> searchInRange(std::vector<std::vector<Key*> > keys);

	virtual ~KDtree();

private:

	//Pide el primer nodo del archivo y lo almacena como raiz.
	void setRoot();

	int insert(Node* root, Record* record);

	unsigned numberOfNodes;
	std::vector<unsigned> freeNodes;

	FileAbstract* treeFile;
	Node* root;

};

#endif /* KD_H_ */
