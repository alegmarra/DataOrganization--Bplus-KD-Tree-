#include "../KDTree/KD.h"
#include "../KDTree/RecordID/ID.h"
#include "../KDTree/RecordID/IntKey.h"
#include "Test.cpp"
#include <vector>
#include <iostream>

#define X 0
#define Y 1
#define Z 2

class KDTreeTest: public Test 
{

private:

    unsigned blockSize;
    unsigned k;
    const char * path;
    const char * spacePath;
    

public:

    KDTreeTest(): Test("KDTree")
    {

        blockSize = 200;
        path = "/tmp/test_FindByQuery.bin";
		spacePath = "/tmp/test_FindByQuery_space.bin";
        k = 3;

        cleanUp();
    }
    
    ~KDTreeTest() 
    {
        remove(path);
		remove(spacePath);
    }

	virtual void run()
	{

		//test_Constructor_NewFile_NoError();

        test_FindByQuery();
	}

private:

    void cleanUp() 
    {
		remove(path);
		remove(spacePath);
	}

    void loadTree(KDtree * tree)
    {
        std::vector< Record * > records_list;
        ID * id;

        int datos[20][3] = {
            {1,  8,  12},
            {8,  8,  14},
            {5,  17, 18},
            {1,  9,  15},
            {1,  15, 13},
            {17, 15, 4},
            {4,  13, 20}, // SPLIT!
            {11, 14, 12},
            {20, 18, 18},
            {8,  18, 13},
            {15, 16, 5},
            {13, 3,  11},
            {20, 7,  1},
            {7,  12, 13},
            {5,  9,  18},
            {4,  17, 17},
            {6,  2,  7},
            {8,  13, 6},
            {19, 15, 2},
            {10, 17, 19}
        };
        
        for (int i = 0; i < 8; i++) {
            id = new ID(k);
            id->addKey(X, new IntKey(datos[i][0], 8));
            id->addKey(Y, new IntKey(datos[i][1], 8));
            id->addKey(Z, new IntKey(datos[i][2], 8));
        
            records_list.push_back(new Record(id));
        }
        
        tree->load(records_list);

    }
    
    void dumpResult(std::vector< Record * > result)
    {
        ID * id;
        IntKey * x;  
        IntKey * y;
        IntKey * z;
  
        std::cout << "========================" << std::endl;
  
        for (int i = 0; i < result.size(); i++) {
            id = result[i]->getID();
            x = dynamic_cast<IntKey *>(id->getKey(X));
            y = dynamic_cast<IntKey *>(id->getKey(Y));
            z = dynamic_cast<IntKey *>(id->getKey(Z));
        
            if (x && y && z) {
                std::cout << "(" << x->getValue() << ", " << y->getValue() << ", " << z->getValue() << ")" << std::endl;
            }
        
        }
    }

    void test_FindByQuery()
    {
        start("FindByQuery");
        
        FileBlocks * f = new FileBlocks(path, blockSize);
        KDtree * tree = new KDtree(k, f);
        Query * q;
        std::vector< Record * > result;
        char error[50];
  
        loadTree(tree);      
return;
        q = new Query();
        q->addCondition(X, new QueryCondition(new IntKey(1, 8)));
  
        result = tree->find(q);
        
        if (result.size() == 3) pass();
        else {
            sprintf(error, "Partial match failed. Expected result size 3. Got %d" , (int)result.size());
            fail(error);
        }
        
        //dumpResult(result);
        delete q;

        q = new Query();
        q->addCondition(Y, new QueryCondition(new IntKey(8, 8), new IntKey(12, 8)));
  
        result = tree->find(q);
        
        if (result.size() == 5) pass();
        else {
            sprintf(error, "Range match failed. Expected result size 5. Got %d" , (int)result.size());
            fail(error);
        }
  
        //dumpResult(result);
        delete q;
        
        q = new Query();
        q->addCondition(X, new QueryCondition(new IntKey(13, 8)));
        q->addCondition(Y, new QueryCondition(new IntKey(3, 8)));
        q->addCondition(Z, new QueryCondition(new IntKey(11, 8)));
        
        result = tree->find(q);
        
        if (result.size() == 1) pass();
        else {
            sprintf(error, "Exact match failed. Expected result size 1. Got %d" , (int)result.size());
            fail(error);
        }
  
        //dumpResult(result);
        delete q;
        
        q = new Query();
        q->addCondition(X, (new QueryCondition())->setLow(new IntKey(10, 8)));
        result = tree->find(q);
        
        if (result.size() == 8) pass();
        else {
            sprintf(error, "Exact match failed. Expected result size 8. Got %d" , (int)result.size());
            fail(error);
        }
  
        //dumpResult(result);
        delete q;
  
        delete tree;

        cleanUp();
        
        stop();
    }

};
