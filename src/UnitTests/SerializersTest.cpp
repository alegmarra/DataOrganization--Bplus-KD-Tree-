#include "Test.cpp"
#include "../KDTree/Serializers/NodeSerializer.h"
#include "../KDTree/Node/LeafNode.h"
#include "../KDTree/Node/InnerNode.h"
#include "../Exceptions/FileNotSetException.h"
#include "../Exceptions/FileErrorException.h"
#include "../KDTree/RecordID/ID.h"
#include "../KDTree/RecordID/Linea.h"
#include "../KDTree/RecordID/FranjaHoraria.h"
#include "../KDTree/RecordID/Falla.h"
#include "../KDTree/RecordID/Accidente.h"
#include "../KDTree/RecordID/Formacion.h"
#include "../KDTree/RecordID/KeyFactory.h"

#include <stdio.h>

#define FILENAME "testFile_nodeSerializer.bin"
#define FILENAME_SPACE "testFile_nodeSerializer_space.bin"

class SerializersTest : public Test {
    public:
        SerializersTest(): Test("Serializers") {
            Record::setDimensions(5);
            KeyFactory::setDimensions(5);
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
            NodeSerializer::freeStaticMem();
			remove(FILENAME);
			remove(FILENAME_SPACE);
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
            start("serializeDeserializeRecord");


            Record* rec = initRecord("Sarmiento", 123456789, "Sin frenos",
                                     "Chocó con tu hermana", 1234);
            char buffer[256];
            int bytes = rec->serialize(buffer);
            Record* recHidratado = new Record();


            if (bytes == recHidratado->deserialize(buffer))
                pass();
            else
                fail("bytes usados NO OK");


            if (rec->getID()->equalsTo(recHidratado->getID()))
                pass();
            else
                fail("ID NO OK");

            stop();
        }

        void test_NodeSerializer_serializeNode_throws_FileNotSet() {
            start("NodeSerializer_serializeNode_throws_FileNotSet");

            NodeSerializer::freeStaticMem();
            LeafNode* n = new LeafNode();
            try {
                NodeSerializer::serializeNode(n, 10);
            }
            catch(const FileNotSetException& e) {
                delete n;
                pass();
                return;
            }

            fail("NO OK ");

            stop();
        }

        void test_NodeSerializer_deserializeNode_throws_FileNotSet() {
            start("NodeSerializer_deserializeNode_throws_FileNotSet");

            NodeSerializer::freeStaticMem();
            try {
                NodeSerializer::deserializeNode(10);
            }
            catch(const FileNotSetException& e) {
            	pass();
                return;
            }

            fail("NO OK ");


            stop();
        }

        void checkNewNodeAssignment(Node* n, unsigned expected) {

        	unsigned nodeNumber = NodeSerializer::serializeNode(n, NEW_NODE);
            if (nodeNumber == expected)
            	pass();
            else{
                std::string s = "NO OK, asginado ";
                		    s += nodeNumber;
                		    s += ", debió ser ";
                		    s += expected;
                fail(s);
            }
            delete n;
        }

        void test_NodeSerializer_serializeNode_assigns_nodeNumber() {
            start("NodeSerializer_serializeNode_assigns_nodeNumber");

        	NodeSerializer::newFile(FILENAME, BLOCKSIZE);
            LeafNode* root = new LeafNode();
            InnerNode* inLeft = new InnerNode();
            InnerNode* inRight = new InnerNode();
            checkNewNodeAssignment(root, 0);
            checkNewNodeAssignment(inLeft, 1);
            checkNewNodeAssignment(inRight, 2);

            stop();
        }

        void test_NodeSerializer_serializeNode_existing_nodeNumber() {

        	start("NodeSerializer_serializeNode_existing_nodeNumber");


        	NodeSerializer::newFile(FILENAME, BLOCKSIZE);
            Node* nodes[3];
            unsigned nodeNumber, expected;
            for (unsigned i = 0; i < 3; ++i) {
                nodes[i] = new LeafNode();
                nodeNumber = NodeSerializer::serializeNode(nodes[i], NEW_NODE);
                expected = NodeSerializer::serializeNode(nodes[i], nodeNumber);
                if (nodeNumber == expected)
                	pass();
                else{
                    std::string s = "NO OK, escrito en "; s+=nodeNumber;
                              	s +=" y debió ser en "; s += expected;
                    fail(s);
                }
                delete nodes[i];
            }

            stop();
        }

        void test_NodeSerializer_serializeDeserializeNode_Leaf() {
            start("NodeSerializer_serializeDeserializeNode_Leaf");

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

            LeafNode* lfHidratado = dynamic_cast<LeafNode* >(nHidratado);
            if (lfHidratado)
            	pass();
            else {
                fail("serialización-deserialización LeafNode NO OK");
                delete lf;
                delete lfHidratado;
                return;
            }

            if (lfHidratado->level == lf->level)
            	pass();
            else
                fail("level NO OK");

            if (lfHidratado->numElements == lf->numElements)
            	pass();
            else
                fail("numElements NO OK");

            ID* idOriginal;
            ID* idHidratado;
            for (unsigned i = 0; i < cant; ++i) {
                idOriginal = lf->elements[i]->getID();
                idHidratado = lfHidratado->elements[i]->getID();
                if (idOriginal->equalsTo(idHidratado))
                	pass();
                else{
                    std::string s="registro "; s+= i; s+=" NO OK";
                    fail(s);
                }
            }

            delete lf;
            delete lfHidratado;

            stop();
        }

        void test_NodeSerializer_serializeDeserializeNode_Inner() {

        	start("NodeSerializer_serializeDeserializeNode_Inner");

        	// ini
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
                    inNodes[i]->elements.push_back(new PairKeyNode(k, (i+2)*(j+3)));
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
                in = dynamic_cast<InnerNode* >(nodesHidratados[i]);
                if (in)
                	pass();
                else {
                    fail("\t\t creción InnerNode \tNO OK");
                    delete nodesHidratados[i];
                    continue;
                }

                if (in->level == inNodes[i]->level)
                	pass();
                else
                    fail("NO OK");


                if (in->numElements == inNodes[i]->numElements)
                	pass();
                else
                    fail("NO OK");


                if (in->firstLeft == inNodes[i]->firstLeft)
                	pass();
                else
                    fail("NO OK");

                PairKeyNode pOriginal;
                PairKeyNode pHidratado;
                for (unsigned j = 0; j < cant; ++j) {

                    pOriginal = *(inNodes[i]->elements[j]);
                    pHidratado = *(in->elements[j]);
                    if (!pHidratado.getKey()->compareTo(pOriginal.getKey()))
                    	pass();
                    else
                        fail("NO OK");


                    if (pHidratado.getNode() == pOriginal.getNode())
                    	pass();
                    else
                        fail("NO OK");
                }

                delete in;

            }

            // fin testing

            for (unsigned i = 0; i < cant; ++i)
                delete inNodes[i];

            stop();
        }



};

