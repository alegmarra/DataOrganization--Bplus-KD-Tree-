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
            test_serializeDeserializeRecord();
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

        void test_serializeDeserializeRecord() {
            std::string info = "test_serializeDeserializeRecord: ";
            Record* rec = initRecord("Sarmiento", 123456789, "Sin frenos",
                                     "Chocó con tu hermana", 1234);
            char buffer[256];
            int bytes = rec->serialize(buffer);
            Record* recHidratado = new Record();

            std::cout << info;
            if (bytes == recHidratado->deserialize(buffer))
                std::cout << "bytes usados OK";
            else
                std::cout << "bytes usados NO OK";

            std::cout << std::endl << info;
            if (rec->getID()->equalsTo(recHidratado->getID()))
                std::cout << "ID OK";
            else
                std::cout << "ID NO OK";
            std::cout << std::endl;

        }

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

        void test_NodeSerializer_serializeDeserializeNode_Leaf() {
            // ini
            std::string info = "test_NodeSerializer_serializeDeserializeNode_Leaf: ";
            NodeSerializer::newFile(FILENAME, BLOCKSIZE);
            int level = 4;
            const unsigned cant = 3;
            std::string lineas[cant] = { "Sarmiento", "Mitre", "Roca"};
            int_least64_t franjasHorarias[3] = { 1337080562LL, 13378000008LL, 1};
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

            std::cout << info;
            if (lfHidratado->level == lf->level)
                std::cout << "level OK";
            else
                std::cout << "level NO OK";

            std::cout << std::endl << info;
            if (lfHidratado->numElements == lf->numElements)
                std::cout << "numElements OK";
            else
                std::cout << "numElements NO OK";

            ID* idOriginal;
            ID* idHidratado;
            for (unsigned i = 0; i < cant; ++i) {
                std::cout << std::endl << info;
                idOriginal = lf->elements[i]->getID();
                idHidratado = lfHidratado->elements[i]->getID();
                if (idOriginal->equalsTo(idHidratado))
                    std::cout << "registro " << i << " OK";
                else
                    std::cout << "registro " << i << " NO OK";
            }

            std::cout << std::endl;

            delete lf;
            delete lfHidratado;
        }

        void test_NodeSerializer_serializeDeserializeNode_Inner() {
            // ini
            std::cout << "test_NodeSerializer_serializeDeserializeNode_Inner: 5 inner nodes, 5 keys\n";
            NodeSerializer::newFile(FILENAME, BLOCKSIZE);
            const unsigned cant = 5;
            std::string lineas[cant] = { "Sarmiento", "Mitre", "Roca", "San Martín", "Tigre" };
            int_least64_t franjasHorarias[cant] = { 1337080562LL, 13378000008LL, 1, 234, 543623 };
            std::string fallas[cant] = { "Frenos andando 40%",
                "Ruedas desalineadas", "Motor roto", "Puertas no abren", "Sin fallas" };
            std::string accidentes[cant] = { "Chocó con otra formación",
                "Descarriló", "Se frenó sin previo aviso", "", "Ninguno" };
            unsigned formaciones[cant] = { 204, 1203, 4, 1, 1337};
            Record* recs[cant];
            InnerNode* inNodes[cant];
            Node* nodesHidratados[cant];
            unsigned nodeNumbers[cant];
            for (unsigned i = 0; i < cant; ++i) {
                recs[i] = initRecord(lineas[i], franjasHorarias[i], fallas[i],
                                     accidentes[i], formaciones[i]);
                inNodes[i] = new InnerNode(i);
                inNodes[i]->firstLeft = i+30;
            }
            Key* k;
            for (unsigned i = 0; i < cant; ++i) {
                for (unsigned j = 0; j < cant; ++j) {
                    k = recs[j]->getID()->getKey(i);
                    inNodes[i]->elements.push_back(PairKeyNode(k, (i+2)*(j+3)));
                }
                inNodes[i]->numElements = inNodes[i]->elements.size();
            }

            // fin ini

            // serialize-deserialize
            for (unsigned i = 0; i < cant; ++i) {
                nodeNumbers[i] = NodeSerializer::serializeNode(inNodes[i], NEW_NODE);
                nodesHidratados[i] = NodeSerializer::deserializeNode(nodeNumbers[i]);
            }
            // fin serialize-deserialize

            // testing
            InnerNode* in;
            for (unsigned i = 0; i < cant; ++i) {
                std::cout << "\t testing node " << i << std::endl;
                in = dynamic_cast<InnerNode* >(nodesHidratados[i]);
                if (in)
                    std::cout << "\t\t creación InnerNode \tOK";
                else {
                    std::cout << "\t\t creción InnerNode \tNO OK";
                    delete nodesHidratados[i];
                    continue;
                }

                std::cout << std::endl << "\t\t level \t\t\t";
                if (in->level == inNodes[i]->level)
                    std::cout << "OK";
                else
                    std::cout << "NO OK";

                std::cout << std::endl << "\t\t numElements \t\t";
                if (in->numElements == inNodes[i]->numElements)
                    std::cout << "OK";
                else
                    std::cout << "NO OK";

                std::cout << std::endl << "\t\t firstLeft \t\t";
                if (in->firstLeft == inNodes[i]->firstLeft)
                    std::cout << "OK";
                else
                    std::cout << "NO OK";

                PairKeyNode pOriginal;
                PairKeyNode pHidratado;
                for (unsigned j = 0; j < cant; ++j) {
                    std::cout << std::endl << "\t\t pair " << j+1 << " \tkeys\t";
                    pOriginal = inNodes[i]->elements[j];
                    pHidratado = in->elements[j];
                    if (!pHidratado.getKey()->compareTo(pOriginal.getKey()))
                        std::cout << "OK";
                    else
                        std::cout << "NO OK";

                    std::cout << "\tnextChild ";
                    if (pHidratado.getNode() == pOriginal.getNode())
                        std::cout << "OK";
                    else
                        std::cout << "NO OK";
                    std::cout << std::endl;
                }
                std::cout << std::endl;
                delete in;
            }
            // fin testing

            for (unsigned i = 0; i < cant; ++i)
                delete inNodes[i];
        }

};

