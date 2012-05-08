/*
 * ID.h
 *
 *  Created on: May 7, 2012
 *      Author: bort
 */

#ifndef ID_H_
#define ID_H_
#include<vector>

#include "Key.h"


class ID {
public:
	ID(std::vector<Key> idKeys): keys(idKeys), size(idKeys.size()){};

	void addKey(Key key);

	std::vector<Key> getKeys();

	virtual ~ID();

private:

	std::vector<Key> keys;
	unsigned size;

};

#endif /* ID_H_ */
