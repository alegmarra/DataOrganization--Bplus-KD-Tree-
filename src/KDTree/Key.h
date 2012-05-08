/*
 * Key.h
 *
 *  Created on: May 7, 2012
 *      Author: bort
 */

#ifndef KEY_H_
#define KEY_H_

#include<cstring>
#include<string>
#include "Comparator.h"

const int MAX_STRN_SIZE = 80;

class Key {
public:
	Key(std::string key);
	Key(unsigned key);

	std::string getKey();

	Comparator* getComparator();

	virtual ~Key();

private:

	long keyValue;
	char keyString[MAX_STRN_SIZE];

	class KeyComparator: public Comparator{

	public:
		KeyComparator(std::string content): Comparator(&content){};

		virtual int compareTo(void * target);

	};

};




#endif /* KEY_H_ */
