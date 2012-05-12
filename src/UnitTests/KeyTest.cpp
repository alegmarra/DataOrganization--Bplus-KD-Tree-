#include "KDTree/Key.h"
#include <iostream>
#include <assert.h>

class KeyTest {

public:

	KeyTest(){

		std::cout << "KeyTest BEGIN: "
				  << std::endl << std::endl;
	}

	void test_StringConstructor_NoError(){

		try{

			new Key("myKey");

		}catch(...){

			std::cout << "test_StringConstructor_NoError: NOT OK"
					  << std::endl;
			assert(false);

		}

		assert(true);
		std::cout << "test_StringConstructor_NoError: OK"
				  << std::endl;


	}

	void test_StringConstructor_Throws_InvalidKeyException(){

		try{

			new Key("");

		}catch(InvalidKeyException& e){

			std::string spected = "Invalid value for a Key";

			assert(spected == e.what());
			std::cout << "test_StringConstructor_Throws_InvalidKeyException: OK"
					  << std::endl;

			return;
		}

		std::cout << "test_StringConstructor_Throws_InvalidKeyException: NOT OK"
				  << std::endl;
		assert(false);

	}

	void test_NumberConstructor_NoError(){

		try{

			new Key(1892);

		}catch(...){

			std::cout << "test_NumberConstructor_NoError: NOT OK"
					  << std::endl;
			assert(false);

		}

		assert(true);
		std::cout << "test_NumberConstructor_NoError: OK"
				  << std::endl;


	}

	void test_NumberConstructor_Throws_InvalidKeyException(){

		try{

			new Key((-1));

		}catch(InvalidKeyException& e){

			std::string spected = "Invalid value for a Key";

			assert(spected == e.what());
			std::cout << "test_NumberConstructor_Throws_InvalidKeyException: OK"
					  << std::endl;

			return;
		}

		std::cout << "test_NumberConstructor_Throws_InvalidKeyException: NOT OK"
				  << std::endl;
		assert(false);

	}

	void test_getKey_NoError(){

		Key* pStringKey = new Key("hello");
		std::string spected = "hello";

		assert(spected == pStringKey->getKey());

		Key* pNumKey = new Key(1990);

		spected = "1990";

		assert(spected == pNumKey->getKey());

		std::cout << "test_getKey_NoError: OK"
				  << std::endl;

		delete pStringKey;
		delete pNumKey;
	}

	void test_KeyComparator_NoError(){

		Comparator* cOrigin = (new Key("hello"))->getComparator();
		Key* targetEQL = new Key("hello");
		Key* targetOVER = new Key("hello world");
		Key* targetUNDER = new Key("h");



		int result = cOrigin->compareTo(targetEQL);

		assert (result == 0);

		result = cOrigin->compareTo(targetOVER);

		assert (result == -1);

		result = cOrigin->compareTo(targetUNDER);

		assert (result == 1);

		std::cout << "test_KeyComparator_NoError: OK"
				  << std::endl;

	}


	virtual ~KeyTest(){

		std::cout << "-------KeyTest END-------"
				  << std::endl << std::endl;
	}

private:

};
