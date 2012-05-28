#include <cstring>
#include "../KDTree/RecordID/StringKey.h"
#include "../KDTree/RecordID/IntKey.h"

#include "Test.cpp"

#define UINT_TEST 0x79ULL

class KeyTest: public Test {

public:

	KeyTest(): Test("Key") { }

	virtual void run(){
        test_StringKey_CompareTo();
        test_StringKey_Serialize();
        test_StringKey_Deserialize();
        test_IntKey_CompareTo();
        test_IntKey_SerializeDeserialize();
	}

    void test_StringKey_CompareTo() {
        std::cout << "test_StringKey_CompareTo: ";

        std::string testStringIgual = "Hey you! Out there in the cold";
        std::string testStringMenor = "AAAA";
        std::string testStringMayor = "ZZZZ";
        StringKey sk(testStringIgual);
        StringKey skIgual(testStringIgual);

        if (sk.compareTo(&skIgual) == 0)
            std::cout << "iguales OK";
        else
            std::cout << "iguales NO OK";
        std::cout << std::endl
                  << "test_StringKey_CompareTo: ";

        StringKey skMenor(testStringMenor);
        if (sk.compareTo(&skMenor) > 0)
            std::cout << "menor OK";
        else
            std::cout << "menor NO OK";
        std::cout << std::endl
                  << "test_StringKey_CompareTo: ";

        StringKey skMayor(testStringMayor);
        if (sk.compareTo(&skMayor) < 0)
            std::cout << "mayor OK";
        else
            std::cout << "mayor NO OK";
        std::cout << std::endl;

    }

    void test_StringKey_Serialize() {
        std::cout << "test_StringKey_Serialize: ";

        std::string testString = "Getting lonely, getting cold";
        StringKey sk(testString);

        char buffer[80];
        int bytes = sk.serialize(buffer);
        int bytesOk = 0;

        for (unsigned i = 0; i <= testString.size(); ++i)
            if (buffer[i] == testString[i])
                ++bytesOk;

        if (bytes == bytesOk)
            std::cout << "OK";
        else
            std::cout << bytesOk << "bytes de " << testString.size();

        std::cout << std::endl;
    }

    void test_StringKey_Deserialize() {
        std::cout << "test_StringKey_Deserialize: ";
        char buffer[80] = "Can you feel me?";
        StringKey skSerializada;
        StringKey skComparadora(buffer);
        unsigned bytes = skSerializada.deserialize(buffer);

        if (bytes == (strlen(buffer)+1) &&
            !skComparadora.compareTo(&skSerializada))
            std::cout << "OK";
        else if (bytes != strlen(buffer)+1)
                std::cout << "cantidad de bytes usados mal";
            else
                std::cout << "mal deserializada";

        std::cout << std::endl;
    }

    void test_IntKey_CompareTo() {
        std::cout << "test_IntKey_CompareTo: ";
        IntKey ik(1234567890, 8);
        IntKey ikIgual(1234567890, 8);

        if (ik.compareTo(&ikIgual) == 0)
            std::cout << "iguales OK";
        else
            std::cout << "iguales NO OK";
        std::cout << std::endl
                  << "test_IntKey_CompareTo: ";

        IntKey ikMenor(12345, 8);
        if (ik.compareTo(&ikMenor) > 0)
            std::cout << "menor OK";
        else
            std::cout << "menor NO OK";
        std::cout << std::endl
                  << "test_IntKey_CompareTo: ";

        IntKey ikMayor(1334567890, 8);
        if (ik.compareTo(&ikMayor) < 0)
            std::cout << "mayor OK";
        else
            std::cout << "mayor NO OK";
        std::cout << std::endl;
    }

    /**
     * @brief hidratación y deshidratación juntas, no se me ocurría otra forma
     *
     * Serializa en el mismo buffer 16 IntKey de 1-8 bytes, intercalando
     * positivos con negativos. Luego hidrata 16 IntKeys, y compara con las
     * 16 primeras, dado que el compareTo está testeado
     */
    void test_IntKey_SerializeDeserialize() {
        // ini
        std::string info = "test_IntKey_SerializeDeserialize: ";
        std::string size = "size ";
        std::string pos = ", positivo ";
        std::string neg = ", negativo ";
        char buffer[80];
        int bytesUsados = 0;
        int bytesLeidos = 0;
        int_least64_t intTestPositivos[8];
        int_least64_t intTestNegativos[8];
        IntKey* intKeysTestPositivos[8];
        IntKey* intKeysTestNegativos[8];
        IntKey* intKeysTestPositivosHidratados[8];
        IntKey* intKeysTestNegativosHidratados[8];

        for (unsigned i = 0; i < 8; ++i) {
            intTestPositivos[i] = UINT_TEST << 8*i;
            intTestNegativos[i] = -(UINT_TEST << 8*i);
            intKeysTestPositivos[i] = new IntKey(intTestPositivos[i], i+1);
            intKeysTestNegativos[i] = new IntKey(intTestNegativos[i], i+1);
            intKeysTestPositivosHidratados[i] = new IntKey(i+1);
            intKeysTestNegativosHidratados[i] = new IntKey(i+1);
        }
        // fin ini

        for (unsigned i = 0; i < 8; ++i) {
            bytesUsados += intKeysTestPositivos[i]->serialize(buffer + bytesUsados);
            bytesUsados += intKeysTestNegativos[i]->serialize(buffer + bytesUsados);
        }

        for (unsigned i = 0; i < 8; ++i) {
            bytesLeidos += intKeysTestPositivosHidratados[i]->deserialize(buffer + bytesLeidos);
            bytesLeidos += intKeysTestNegativosHidratados[i]->deserialize(buffer + bytesLeidos);
        }

        std::cout << info;
        if (bytesUsados == bytesLeidos)
            std::cout << "bytes usados y leídos OK" << std::endl;
        else
            std::cout << "bytes usados y leídos NO OK" << std::endl;

        for (unsigned i = 0; i < 8; ++i) {
            std::cout << info << size << i+1 << pos;
            if (!intKeysTestPositivosHidratados[i]->compareTo(intKeysTestPositivos[i]))
                std::cout << "OK" << std::endl;
            else
                std::cout << "NO OK" << std::endl;

            std::cout << info << size << i+1 << neg;
            if (!intKeysTestNegativosHidratados[i]->compareTo(intKeysTestNegativos[i]))
                std::cout << "OK" << std::endl;
            else
                std::cout << "NO OK" << std::endl;
        }

        for (unsigned i = 0; i < 8; ++i) {
            delete intKeysTestPositivos[i];
            delete intKeysTestNegativos[i];
            delete intKeysTestPositivosHidratados[i];
            delete intKeysTestNegativosHidratados[i];
        }
    }


};
