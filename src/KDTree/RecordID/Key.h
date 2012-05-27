/*
* Key.h
*
* Created on: May 7, 2012
* Author: AleMarra
*/

#ifndef KEY_H_
#define KEY_H_

#include "../../Exceptions/InvalidKeyException.cpp"
#include "../Serializers/Serializable.h"
/**
 * @todo llenar la clase de responsabilidades para las que hereden
 */

class Key : public Serializable {
    public:
        /**
         * @return >0 si this > k
         *          0 si this == k
         *         <0 si this < k
         * @throw InvalidKeyException
         */
        virtual int compareTo(Key * k) = 0;
};

#endif /* KEY_H_ */
