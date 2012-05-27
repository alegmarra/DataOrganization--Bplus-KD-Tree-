#include "Test.cpp"
#include "../KDTree/Serializers/NodeSerializer.h"
#include "../KDTree/LeafNode.h"
#include "../KDTree/InnerNode.h"
#include "../Exceptions/FileNotSetException.h"
#include "../Exceptions/FileErrorException.h"
#include "../KDTree/RecordID/ID.h"
#include "../KDTree/RecordID/Linea.h"
#include "../KDTree/RecordID/FranjaHoraria.h"
#include "../KDTree/RecordID/Falla.h"
#include "../KDTree/RecordID/Accidente.h"
#include "../KDTree/RecordID/Formacion.h"

#define FILENAME "testFile_nodeSerializer.bin"

class SerializersTest : public Test {
    public:
        SerializersTest() {
            std::cout << std::endl << "SerializersTest BEGIN: "
                      << std::endl << std::endl;

        }

        void run() {
            test_NodeSerializer_serializeNode_throws_FileNotSet();
            test_NodeSerializer_deserializeNode_throws_FileNotSet();
            test_NodeSerializer_serializeNode_assigns_nodeNumber();
            test_NodeSerializer_serializeNode_existing_nodeNumber();
            test_NodeSerializer_serializeDeserializeNode_Leaf();
            test_NodeSerializer_serializeDeserializeNode_Inner();
        }

        ~SerializersTest() {
            std::cout << "-------SerializersTest END-------"
                      << std::endl;
            NodeSerializer::freeStaticMem();
        }

    private:
        void test_NodeSerializer_serializeNode_throws_FileNotSet() {
            std::cout << "test_NodeSerializer_serializeNode_throws_FileNotSet: ";

            NodeSerializer::freeStaticMem();
            LeafNode* n = new LeafNode();
            try {
                NodeSerializer::serializeNode(n, 10);
            }
            catch(const FileNotSetException& e) {
                delete n;
                std::cout << "OK" << std::endl;
                return;
            }

            std::cout << "NO OK" << std::endl;
        }

        void test_NodeSerializer_deserializeNode_throws_FileNotSet() {
            std::cout << "test_NodeSerializer_deserializeNode_throws_FileNotSet: ";

            NodeSerializer::freeStaticMem();
            try {
                NodeSerializer::deserializeNode(10);
            }
            catch(const FileNotSetException& e) {
                std::cout << "OK" << std::endl;
                return;
            }

            std::cout << "NO OK" << std::endl;
        }

        void checkNewNodeAssignment(Node* n, unsigned expected) {
            std::cout << "test_NodeSerializer_serializeNode_assigns_nodeNumber: ";
            unsigned nodeNumber = NodeSerializer::serializeNode(n, NEW_NODE);
            if (nodeNumber == expected)
                std::cout << "OK, asignado " << nodeNumber;
            else
                std::cout << "NO OK, asginado " << nodeNumber
                          << ", debió ser " << expected;
                std::cout << std::endl;
            delete n;
        }

        void test_NodeSerializer_serializeNode_assigns_nodeNumber() {
            NodeSerializer::newFile(FILENAME, BLOCKSIZE);
            LeafNode* root = new LeafNode();
            InnerNode* inLeft = new InnerNode();
            InnerNode* inRight = new InnerNode();
            checkNewNodeAssignment(root, 0);
            checkNewNodeAssignment(inLeft, 1);
            checkNewNodeAssignment(inRight, 2);
        }

        void test_NodeSerializer_serializeNode_existing_nodeNumber() {


            NodeSerializer::newFile(FILENAME, BLOCKSIZE);
            Node* nodes[3];
            unsigned nodeNumber, expected;
            for (unsigned i = 0; i < 3; ++i) {
                std::cout << "test_NodeSerializer_serializeNode_existing_nodeNumber: ";
                nodes[i] = new LeafNode();
                nodeNumber = NodeSerializer::serializeNode(nodes[i], NEW_NODE);
                expected = NodeSerializer::serializeNode(nodes[i], nodeNumber);
                if (nodeNumber == expected)
                    std::cout << "OK, actualizado bloque " << nodeNumber;
                else
                    std::cout << "NO OK, escrito en " << nodeNumber
                              << " y debió ser en " << expected;
                std::cout << std::endl;
                delete nodes[i];
            }
        }
        Record* initRecord(const std::string& linea,
                           int_least64_t franjaHoraria,
                           const std::string& falla,
                           const std::string& accidente,
                           int formacion) {
            ID* id = new ID(K);
            id->addKey(LINEA, new Linea(linea));
            id->addKey(FRANJA, new FranjaHoraria(franjaHoraria));
            id->addKey(FALLA, new Falla(falla));
            id->addKey(ACCIDENTE, new Accidente(accidente));
            id->addKey(FORMACION, new Formacion(formacion));
            return new Record(id);
        }

        void test_NodeSerializer_serializeDeserializeNode_Leaf() {
            // ini
            std::string info = "test_NodeSerializer_serializeDeserializeNode_Leaf: ";
            NodeSerializer::newFile(FILENAME, BLOCKSIZE);
            int level = 4;
            const unsigned cant = 3;
            std::string lineas[cant] = { "Sarmiento", "Mitre", "Roca"};
            int_least64_t franjasHorarias[3] = { 1337080562LL, 1337800000LL, 1};
            std::string fallas[cant] = { "Frenos andando 40%",
                "Ruedas desalineadas", "Motor roto" };
            std::string accidentes[cant] = { "Chocó con otra formación",
                "Descarriló", "Se frenó sin previo aviso" };
            unsigned formaciones[cant] = { 204, 1203, 4};
            LeafNode* lf = new LeafNode(level);
            for (unsigned i = 0; i < cant; ++i) {
                Record* rec = initRecord(lineas[i], franjasHorarias[i], fallas[i],
                                         accidentes[i], formaciones[i]);
                lf->elements.push_back(rec);
            }
            lf->numElements = lf->elements.size();
            // fin ini

            unsigned nodeNumber = NodeSerializer::serializeNode(lf, NEW_NODE);
            Node* nHidratado = NodeSerializer::deserializeNode(nodeNumber);

            std::cout << info;
            LeafNode* lfHidratado = dynamic_cast<LeafNode* >(nHidratado);
            if (lfHidratado)
                std::cout << "serialización-deserialización LeafNode OK" << std::endl;
            else {
                std::cout << "serialización-deserialización LeafNode NO OK" << std::endl;
                delete lf;
                delete lfHidratado;
                return;
            }



            std::cout << "@todo terminar" << std::endl;
        }

        void test_NodeSerializer_serializeDeserializeNode_Inner() {
            std::cout << "test_NodeSerializer_serializeDeserializeNode_Inner: ";

            std::cout << "@todo" << std::endl;
        }

};

