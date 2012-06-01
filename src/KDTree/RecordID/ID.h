/*
 * ID.h
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#ifndef ID_H_
#define ID_H_
#include <cstdlib>
#include <vector>

#include "Key.h"

enum t_Key{ t_Linea, t_Franja, t_Falla, t_Accidente, t_Formacion };

class Linea;
class FranjaHoraria;
class Falla;
class Accidente;
class Formacion;

class ID : public Serializable {
public:
	ID(unsigned dimensions);

    /**
     * @param dimension pertenece a [0; size)
     * @throw NonExistingDimensionException
     */
	void addKey(unsigned dimension, Key* key);
	void addKey(t_Key type, Key* key);

	/** especializaciones para el TP */
	void addKey(Linea* k);
	void addKey(FranjaHoraria* k);
	void addKey(Falla* k);
	void addKey(Accidente* k);
	void addKey(Formacion* k);

    /**
     * @param dimension pertenece a [0; size)
     * @throw NonExistingDimensionException
     */
	Key* getKey(unsigned dimension);
	Key* getKey(t_Key type);

	unsigned getDimensions();
	unsigned getSize();

    /** iguales si son de igual dimensión e iguales todas las claves */
    bool equalsTo(ID* id);

	int serialize(char* buffer);
	int deserialize(const char* buffer);

    void dump();

	virtual ~ID();

private:

	std::vector<Key*> keys;
	unsigned dimensions;
};

#endif /* ID_H_ */
