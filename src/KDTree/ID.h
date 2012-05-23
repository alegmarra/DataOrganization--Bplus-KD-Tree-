/*
 * ID.h
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#ifndef ID_H_
#define ID_H_
#include <stdlib.h>
#include<map>

#include "Key.h"

enum t_Key{ Linea, Franja, Falla, Accidente, Formacion };

class ID {
public:
	ID(std::map<t_Key,Key>* idKeys);

	void addKey(t_Key type, Key* key);

	Key* getKey(t_Key type);

	unsigned getSize();

	virtual ~ID();

private:

	std::map<t_Key,Key>* keys;
	unsigned size;

};

#endif /* ID_H_ */
