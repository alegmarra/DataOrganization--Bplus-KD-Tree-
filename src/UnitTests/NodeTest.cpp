#ifndef NODE_TEST_CPP
#define NODE_TEST_CPP

#include <stdio.h>
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
	}

	virtual void run(){

		test_EmptyConstructors_NoError();

		test_LevelConstructors_NoError();

		test_Insert_NoError();

		test_Insert_RecordAlreadyExists_Error();

/*		test_LeafGrow_NoError();

		test_InnerInsert_Overflow_Error();

		test_Find_NoError();

		test_Find_NotFound_Error();

		test_LeafInsert_Overflow_Error();

		test_LeafSplit_NoError();

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
        ID* id = new ID(3);

        id->addKey(0, new IntKey(20, 8));
        id->addKey(1, new IntKey(30, 8));
        id->addKey(2, new IntKey(70, 8));
        Record* rec = new Record(id);
        // Primera inserción, debería poder
        int res = root->insert(rec);
        unsigned numElements;
        if (res == 1)
            pass();
        else {
            std::ostringstream oss;
            oss << "LeafNode::insert(...) returned " << res << ", should have been 1";
            fail(oss.str());
        }
        numElements = root->getNumElements();
        if (numElements == 1)
            pass();
        else {
            std::ostringstream oss;
            oss << "NumElements = " << numElements << ", should have been 1";
            fail(oss.str());
        }

        stop();
    }

    void test_Insert_RecordAlreadyExists_Error() {
        start("Insert_RecordAlreadyExists_Error");
        treeFile->deleteData();

        Node* root = new LeafNode(0);
        ID* id = new ID(3);

        id->addKey(0, new IntKey(20, 8));
        id->addKey(1, new IntKey(30, 8));
        id->addKey(2, new IntKey(70, 8));
        Record* rec = new Record(id);
        // Primera inserción, debería poder
        root->insert(rec);

        //Reinserto el mismo registro, no debería
        int res = root->insert(rec);
        unsigned numElements = root->getNumElements();
        if (res == 3)     pass();
        else {
            std::ostringstream oss;
            oss << "LeafNode::insert(...) returned " << res << ", should have been 3";
            fail(oss.str());
        }
        if (root->getNumElements() == 1)
            pass();
        else{
            std::ostringstream oss;
            oss << "NumElements = " << numElements << ", should have been 1";
            fail(oss.str());
        }



        stop();
    }

	void test_LeafGrow_NoError(){
//	    start("LeafGrow_NoError");
//
//        Node* root = new LeafNode(0);
//
//
//        stop();
	}


};

#endif
