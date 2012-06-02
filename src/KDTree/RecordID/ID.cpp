#include "ID.h"
#include <iostream>
#include "KeyFactory.h"
#include "../../Exceptions/NonExistingDimensionException.h"
#include "Linea.h"
#include "FranjaHoraria.h"
#include "Falla.h"
#include "Accidente.h"
#include "Formacion.h"


ID::ID(unsigned _dimensions) : keys(_dimensions), dimensions(_dimensions) {}

void ID::addKey(unsigned dimension, Key* key){

    if (dimension >= dimensions)
        throw NonExistingDimensionException(dimension, dimensions);

	keys[dimension] = key;
}

void ID::addKey(Linea* k) {
    keys[LINEA] = k;
}

void ID::addKey(FranjaHoraria* k) {
    keys[FRANJA] = k;
}

void ID::addKey(Falla* k) {
    keys[FALLA] = k;
}

void ID::addKey(Accidente* k) {
    keys[ACCIDENTE] = k;
}

void ID::addKey(Formacion* k) {
    keys[FORMACION] = k;
}

Key* ID::getKey(unsigned dimension){
    if (dimension >= dimensions)
        throw NonExistingDimensionException(dimension, dimensions);

	return keys[dimension];
}

unsigned ID::getSize(){
    int size = 0;

    for (unsigned i = 0; i < dimensions; ++i)
    	size += keys[i]->getSize();

    return size;
}

unsigned ID::getDimensions(){
	return dimensions;
}


ID::~ID() {
	std::vector<Key* >::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it)
        delete *it;
}

int ID::serialize(char* buffer) {
	int bytes = 0;
	for (unsigned i = 0; i < dimensions; ++i)
        bytes += keys[i]->serialize(buffer + bytes);

    return bytes;
}

int ID::deserialize(const char* buffer) {
    keys.empty();

	int bytes = 0;
	for (unsigned i = 0; i < dimensions; ++i) {
	    keys[i] = KeyFactory::getKey(i);
        bytes += keys[i]->deserialize(buffer + bytes);
	}

    return bytes;
}

bool ID::equalsTo(ID* id) {
    bool iguales = dimensions == id->dimensions;
    unsigned i = 0;
    while (iguales && i < dimensions) {
        iguales = !keys[i]->compareTo(id->keys[i]);
        ++i;
    }

    return iguales;
}

void ID::dump()
{
    std::cout << "(";

    for (int i = 0; i < dimensions; i++) {
        keys.at(i)->dump();

        if (i < dimensions - 1) {
            std::cout << ",";
        }
    }

    std::cout << ")";
}
