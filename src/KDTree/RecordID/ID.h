#ifndef ID_H_
#define ID_H_

#include <cstdlib>
#include <vector>

#include "Key.h"

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
