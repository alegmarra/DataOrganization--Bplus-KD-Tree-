#ifndef NODE_TEST_CPP
#define NODE_TEST_CPP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include "Test.cpp"
#include "../KDTree/Node/InnerNode.h"
#include "../KDTree/Node/LeafNode.h"
#include "../KDTree/Serializers/NodeSerializer.h"
#include "../File/FileBlocks.h"
#include "../KDTree/RecordID/IntKey.h"
#include "../KDTree/RecordID/ID.h"

class NodeTest: public Test{

private:

	FileBlocks* treeFile;
	const char * path;
	unsigned blockSize;

public:

	NodeTest(): Test("NodeTest"){

		path = "my_Node_test_file.bin";
		blockSize = 4096;

		treeFile = new FileBlocks(path, blockSize);
		NodeSerializer::setFile(treeFile);
        srand(time(NULL));
    }

    Record* getRandRecord(unsigned dimensions = 3) {

        ID* id = new ID(dimensions);

        for (unsigned i = 0; i < dimensions; ++i)
            id->addKey(i, new IntKey( rand(), 8));

        return new Record(id);
    }

    void failVerbose(int value, int expected, const char* msg) {
        std::ostringstream oss;
        oss << msg << value << ", should have been " << expected;
        fail(oss.str());
    }

	virtual void run(){

		test_EmptyConstructors_NoError();

		test_LevelConstructors_NoError();

		test_Insert_NoError();

		test_Insert_RecordAlreadyExists_Error();

		test_LeafInsert_Overflow_Error();

		test_LeafSplit_NoError();

		test_LeafGrow_NoError();

/*		test_InnerInsert_Overflow_Error();

		test_Find_NoError();

		test_Find_NotFound_Error();

*/
	}

	void test_EmptyConstructors_NoError(){

        start("EmptyConstructors_NoError");

		Node* leaf = new LeafNode();
		Node* inner = new InnerNode();

		if (leaf->getNumElements() == 0) pass();
		else fail("Wrong number of elements on Leaf EmptyConstructor");

		if (leaf->getLevel() == 0) pass();
		else fail("Wrong level on Leaf EmptyConstructor");

		if (inner->getNumElements() == 0) pass();
		else fail("Wrong number of elements on Inner EmptyConstructor");

		if (inner->getLevel() == 0) pass();
		else fail("Wrong level on Inner EmptyConstructor");

		delete leaf;
		delete inner;

		stop();
	}

	void test_LevelConstructors_NoError(){

        start("LevelConstructors_NoError");

		Node* leaf = new LeafNode(2);
		Node* inner = new InnerNode(1);

		if (leaf->getNumElements() == 0) pass();
		else fail("Wrong number of elements on Leaf Constructor");

		if (leaf->getLevel() == 2) pass();
		else fail("Wrong level on Leaf Constructor");

		if (inner->getNumElements() == 0) pass();
		else fail("Wrong number of elements on Inner Constructor");

		if (inner->getLevel() == 1) pass();
		else fail("Wrong level on Inner Constructor");

		delete leaf;
		delete inner;

		stop();

	}

    void test_Insert_NoError() {
        start("Insert_NoError");
        treeFile->deleteData();

        Node* root = new LeafNode(0);
        Record* rec = getRandRecord();

        int res = root->insert(rec);
        unsigned numElements;
        if (res == 1)
            pass();
        else
            failVerbose(res, 1, "LeafNode::insert(...) returned ");

        numElements = root->getNumElements();
        if (numElements == 1)
            pass();
        else
            failVerbose(numElements, 1, "NumElements = ");

        rec = getRandRecord();

        res = root->insert(rec);
        if (res == 1)
            pass();
        else
            failVerbose(res, 1, "LeafNode::insert(...) returned ");

        numElements = root->getNumElements();
        if (numElements == 2)
            pass();
        else
            failVerbose(numElements, 2, "NumElements = ");

        delete root;
        stop();
    }

    void test_Insert_RecordAlreadyExists_Error() {
        start("Insert_RecordAlreadyExists_Error");
        treeFile->deleteData();

        Node* root = new LeafNode(0);
        Record* rec = getRandRecord();
        // Primera inserción, debería poder
        root->insert(rec);

        //Reinserto el mismo registro, no debería
        int res = root->insert(rec);
        unsigned numElements = root->getNumElements();
        if (res == 3)     pass();
        else
            failVerbose(res, 3, "LeafNode::insert(...) returned ");

        numElements = root->getNumElements();
        if (numElements == 1)
            pass();
        else
            failVerbose(numElements, 1, "NumElements = ");

        delete root;
        stop();
    }

    void test_LeafInsert_Overflow_Error() {
        start("LeafInsert_Overflow_Error");
        treeFile->deleteData();

        Node* root = new LeafNode(0);
        int maxElements = (blockSize * 0.75) / getRandRecord()->size();  // memory leak :D
        for (int i = 0; i < maxElements-1; ++i)
            root->insert(getRandRecord());

        unsigned numElements = root->getNumElements();
        if (numElements == maxElements-1)
            pass();
        else
            failVerbose(numElements, maxElements-1, "Inserted records ");

        int res = root->insert(getRandRecord());
        if (res == 2)
            pass();
        else
            failVerbose(res, 2, "LeafNode::insert(...) returned ");

        delete root;
        stop();
    }

    void test_LeafSplit_NoError() {
        start("LeafSplit_NoError");

        treeFile->deleteData();
        const unsigned level = 1;
        Node* root = new LeafNode(0);
        Node* splittingLeafNode = new LeafNode(level);
        std::map<int, Record*> records;
        Record* temp;
        IntKey* k;
        int maxElements = (blockSize * 0.75) / getRandRecord()->size();  // memory leak :D
        for (int i = 0; i < maxElements; ++i) {
            temp = getRandRecord();
            k = dynamic_cast<IntKey* >(temp->getID()->getKey(level-1));
            while (records.find(k->getValue()) != records.end()) {
                delete temp;
                temp = getRandRecord();
                k = dynamic_cast<IntKey* >(temp->getID()->getKey(level-1));
            }

            records.insert(std::pair<int, Record*>(k->getValue(), temp));
            splittingLeafNode->insert(temp);
        }

        unsigned numElements = splittingLeafNode->getNumElements();
        assert(numElements == records.size());
        // la mitad de size+1 para el newNode
        Node* newNode;
        Key* medianKeyFromSplit = splittingLeafNode->split(newNode);

        unsigned newNodeLevel = newNode->getLevel();
        if (newNodeLevel == level)
            pass();
        else
            failVerbose(newNodeLevel, level, "new node level = ");

        unsigned splittedNumElements = splittingLeafNode->getNumElements();
        unsigned newNodeNumElements = newNode->getNumElements();
        if (splittedNumElements == numElements/2)
            pass();
        else
            failVerbose(splittedNumElements, numElements/2, "splitted node numElements = ");

        if (newNodeNumElements == (1+numElements)/2)
            pass();
        else
            failVerbose(newNodeNumElements, (1+numElements)/2, "new node numElements = ");

        IntKey* medianIntKeyFromSplit = dynamic_cast<IntKey* >(medianKeyFromSplit);

        std::map<int, Record*>::iterator it = records.find(medianIntKeyFromSplit->getValue());
        std::map<int, Record*>::iterator itMitad = records.begin();
        for (unsigned i = 0; i < numElements/2; ++i)
            ++itMitad;

        if (it == itMitad)
            pass();
        else
            fail("Wrong median key value assingment");

        std::map<int, Record*> newNodeElements(itMitad, records.end());
        records.erase(itMitad, records.end());
        unsigned i = 0;
        for (it = records.begin(); it != records.end(); ++it, ++i) {
            temp = ((LeafNode*)splittingLeafNode)->elements[i];
            k = dynamic_cast<IntKey* >(temp->getID()->getKey(level-1));
            if ((*(records.find(k->getValue()))).second == temp)
                pass();
            else
                fail("Wrong element assingment in splitting node");
        }
        i = 0;
        for (it = newNodeElements.begin(); it != newNodeElements.end(); ++it, ++i) {
            temp = ((LeafNode*)newNode)->elements[i];
            k = dynamic_cast<IntKey* >(temp->getID()->getKey(level-1));
            if ((*(newNodeElements.find(k->getValue()))).second == temp)
                pass();
            else
                fail("Wrong element assingment in splitting node");
        }

        delete splittingLeafNode;
        delete newNode;
        delete root;
        stop();
    }

	void test_LeafGrow_NoError(){
	    start("LeafGrow_NoError");
        treeFile->deleteData();

        Node* root = new LeafNode(0);
        int maxElements = (blockSize * 0.75) / getRandRecord()->size();  // memory leak :D
        for (int i = 0; i < maxElements; ++i)
            root->insert(getRandRecord());

        root = root->grow();
        InnerNode* grownRoot = dynamic_cast<InnerNode* >(root);
        if (grownRoot)
            pass();
        else
            fail("LeafNode didn't become InnerNode");

        if (grownRoot->getLevel() == 0)
            pass();
        else
            failVerbose(grownRoot->getLevel(), 0, "grown root level = ");

        stop();
	}


};

#endif
