/*
 * Key.h
 *
 *  Created on: May 7, 2012
 *      Author: AleMarra
 */

#ifndef KEY_H_
#define KEY_H_

#include<cstring>
#include<string>
#include "Comparator.h"
#include "Exceptions/InvalidKeyException.cpp"
#include "Exceptions/InvalidTargetException.cpp"


const int MAX_STRN_SIZE = 80;

class Key {
public:

	//Throws InvalidKeyException
	Key(std::string key);
	Key(long key);

	std::string getKey();

	Comparator* getComparator();

	virtual ~Key();

private:

	long keyValue;
	char keyString[MAX_STRN_SIZE];


	class KeyComparator: public Comparator{

	public:
		KeyComparator(std::string content):
			Comparator(&content), myKey(content){};

		virtual int compareTo(void * target);

	private:

		std::string myKey;

	};


};




#endif /* KEY_H_ */
