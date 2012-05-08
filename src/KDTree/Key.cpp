/*
 * Key.cpp
 *
 *  Created on: May 7, 2012
 *      Author: bort
 */

#include "Key.h"
#include <sstream>



Key::Key(std::string key){
		keyValue = -1;

		strncpy(keyString, key.c_str(), MAX_STRN_SIZE -1);
		keyString[MAX_STRN_SIZE -1] = '\0';
}

Key::Key(unsigned key){
		keyValue = key;
		strcpy(keyString, "");
}

std::string Key::getKey(){

	std::stringstream out;

	if (keyValue == -1) return keyString;
	else{
		out << keyValue;
		return out.str();
	}


}

int Key::KeyComparator::compareTo(void* target){

	try{
		std::string myKey = * ((std::string *)obj);
		std::string targetKey = * ((std::string *)target);

		int result = myKey.compare(targetKey);

		if ( result > 0 ) return 1;
		else if (result < 0 ) return -1;
			 else return result;

	}catch(...){

		return -2;
	}

}

Comparator* Key::getComparator(){

	return new KeyComparator(getKey());

}

Key::~Key() {
	// TODO Auto-generated destructor stub
}


