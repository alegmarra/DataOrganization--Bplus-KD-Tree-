/*
 * ID.cpp
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#include "ID.h"
#include "KeyFactory.h"
#include "../../Exceptions/NonExistingDimensionException.h"

ID::ID(unsigned _size) : keys(_size), size(_size) {}

void ID::addKey(unsigned dimension, Key* key){
    if (dimension >= size)
        throw NonExistingDimensionException(dimension, size);

	keys[dimension] = key;
}

void ID::addKey(t_Key type, Key* key){
	keys[type] = key;
}

Key* ID::getKey(unsigned dimension){
    if (dimension >= size)
        throw NonExistingDimensionException(dimension, size);

	return keys[dimension];
}

Key* ID::getKey(t_Key type){
	return keys[type];
}

unsigned ID::getSize(){
	return size;
}


ID::~ID() {
	std::vector<Key* >::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it)
        delete *it;
}

int ID::serialize(char* buffer) {
	int bytes = 0;
	for (unsigned i = 0; i < size; ++i)
        bytes += keys[i]->serialize(buffer + bytes);

    return bytes;
}

int ID::deserialize(const char* buffer) {
    keys.empty();

	int bytes = 0;
	for (unsigned i = 0; i < size; ++i) {
	    keys[i] = KeyFactory::getKey(i);
        bytes += keys[i]->deserialize(buffer + bytes);
	}

    return bytes;
}

bool ID::equalsTo(ID* id) {
    bool iguales = size == id->size;
    unsigned i = 0;
    while (iguales && i < size) {
        iguales = !keys[i]->compareTo(id->keys[i]);
        ++i;
    }

    return iguales;
}
