#include "../KDTree/KD.h"
#include "../KDTree/RecordID/ID.h"
#include "../KDTree/RecordID/IntKey.h"
#include "Test.cpp"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../KDTree/RecordID/Linea.h"
#include "../KDTree/RecordID/FranjaHoraria.h"
#include "../KDTree/RecordID/Falla.h"
#include "../KDTree/RecordID/Accidente.h"
#include "../KDTree/RecordID/Formacion.h"
#include "../KDTree/RecordID/KeyFactory.h"

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
    int q;
    std::vector< Record * > records_list;



public:

    KDTreeTest(int _q): Test("KDTree")
    {
        srand(time(NULL));
        q=_q;
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
		try {
			//test_Constructor_NewFile_NoError();

		    test_FindByQuery();
		    //test_Full_NonSense_records();

		} catch (...) {
			cleanUp();
			throw;
		}

	}

private:

    void cleanUp()
    {
		remove(path);
		remove(spacePath);
	}

    void loadTree(KDtree * tree)
    {
        ID * id;
        KeyFactory::setDimensions(3);

int datos[100][3] = {
{13,13,16},
{14,18,12},
{18,20,8},
{6,4,4},
{2,9,10},
{1,2,2},
{17,18,18}, // 7 SPLIT
{17,3,12},
{2,18,13},
{7,13,5},
{11,7,19},
{19,17,3},
{13,1,6},// 13 SPLIT
{2,5,18},// 14 SPLIT
{14,15,5},
{1,9,15},
{1,15,13},
{17,15, 4},
{11,10,7},
{7,19,19},
{3,18,19},
{12,6,5},
{14,7,5},
{3,10,5},
{20,4,11},
{12,9,8},
{8,2,16},
{14,11,9},
{18,3,11},
{19,13,16},
{9,16,20}, // EXACT
{6,3,6},
{4,19,17},
{9,16,9},
{5,4,5},
{20,3,15},
{7,8,9},
{5,18,9},
{17,19,18},
{1,18,10},
{6,1,18},
{4,13,11},
{10,15,19},
{14,20,17},
{9,13,3},
{15,18,17},
{3,16,9},
{6,18,1},
{2,4,20},
{18,2,11},
{14,5,9},
{16,14,4},
{9,5,11},
{14,8,19},
{1,3,18},
{14,1,9},
{14,15,20},
{1,2,4},
{16,17,1},
{8,7,3},
{8,15,19},
{8,3,7},
{11,1,1},
{4,19,7},
{16,11,13},
{12,17,11},
{6,8,17},
{1,16,11},
{16,11,15},
{16,15,8},
{20,1,6},
{5,14,3},
{2,7,17},
{19,18,2},
{6,2,5},
{19,14,20},
{8,7,12},
{12,8,10},
{13,19,4},
{8,13,14},
{11,14,7},
{19,4,8},
{4,13,4},
{9,10,17},
{15,14,1},
{3,17,18},
{4,12,15},
{3,18,8},
{14,10,9},
{3,11,10},
{5,14,19},
{1,11,3},
{8,4,5},
{11,11,18},
{20,19,20},
{4,12,13},
{8,20,10},
{19,7,9},
{5,1,14},
{8,17,4}
};
/*
*/
        int limit = q < 100? q : 100;
        for (int i = 0; i < limit; i++) {
            id = new ID(k);
            id->addKey(X, new IntKey(datos[i][0], 8));
            id->addKey(Y, new IntKey(datos[i][1], 8));
            id->addKey(Z, new IntKey(datos[i][2], 8));

            records_list.push_back(new Record(id));
        }
        tree->load(records_list);

tree->dump();

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
//return;

        q = new Query();
        int search =  1;

        q->addCondition(X, new QueryCondition(new IntKey(search, 8)));

        result = tree->find(q);

        int expected = 0;
        ID * id;
        IntKey * x;
        for (int i = 0; i < records_list.size(); i++) {
        	id = records_list[i]->getID();
            x = dynamic_cast<IntKey *>(id->getKey(X));

            if((x->getValue() ==search)){
            	expected++;
            }
        }

        dumpResult(result);
        std::cout << "Partial X = 1" << std::endl;

        if (result.size() == expected) pass();
        else {
        	std::cout << "PARTIAL match failed for " << search <<  " Expected result " << expected << " got " <<   (int)result.size() <<std::endl;
          //  sprintf(error, "Partial match failed. Expected result size %d. Got %d" ,(int)expected, (int)result.size());
  //          fail(error);
        }

        delete q;
//return;


        int low = 4;
        int high = 13;
        q = new Query();

        Key* l = new IntKey(low, 8);
        Key* h = new IntKey(high, 8);

        q->addCondition(Z, new QueryCondition(l,h));
  
        result = tree->find(q);

        expected= 0;
        IntKey * z;

        for (int i = 0; i < records_list.size(); i++) {
            id = records_list[i]->getID();
            z = dynamic_cast<IntKey *>(id->getKey(Z));

            if((z->getValue() >=low) && (z->getValue() <=high)){
            	expected++;
            }
        }


        dumpResult(result);
        std::cout << "Partial  4<= Z <= 13" << std::endl;


        if	(result.size() == expected) pass();
        else {
        	std::cout << "Partial match failed. Expected result " << expected << " got " <<   (int)result.size() <<std::endl;
           // sprintf(error, "Partial match failed. Expected result size %d. Got %d" ,(int)expected, (int)result.size());
            //fail(error);
        }

        delete q;
//return;
        q = new Query();
        q->addCondition(X, new QueryCondition(new IntKey(9, 8)));
        q->addCondition(Y, new QueryCondition(new IntKey(16, 8)));
        q->addCondition(Z, new QueryCondition(new IntKey(20, 8)));

        result = tree->find(q);
        


        dumpResult(result);
        std::cout << "EXACT X=9; Y= 16; Z= 20" << std::endl;


        if (result.size() == 1) pass();
        else {
        	std::cout << "Exact record match failed" <<std::endl;

        	//sprintf(error, "Exact match failed. Expected result size 1. Got %d" , (int)result.size());
            //fail(error);
        }

        delete q;
//return;
        q = new Query();

        low= 10;

        q->addCondition(X, (new QueryCondition())->setLow(new IntKey(low, 8)));
        result = tree->find(q);

        expected= 0;

        for (int i = 0; i < records_list.size(); i++) {
            id = records_list[i]->getID();
            x = dynamic_cast<IntKey *>(id->getKey(X));

            if((x->getValue() >= low)){
            	expected++;
            }
        }


        dumpResult(result);

        std::cout << "PARTIAL X>= " << low << std::endl;


        if (result.size() == expected) pass();
        else {
        	std::cout << "Partial match failed. Expected result " << expected << " got " <<   (int)result.size() <<std::endl;

//            sprintf(error, "Exact match failed. Expected result size 8. Got %d" , (int)result.size());
      //      fail(error);
        }

        delete q;

        delete tree;

        cleanUp();

        stop();
    }

    Record* getRand_NonSense_Record() {
        ID* id = new ID(k);
        std::string auxString;
        int stringSize = rand() % 10 + 5;
        for (int i = 0; i < stringSize; ++i)
            auxString += rand() % 25 + 65;
        id->addKey(new Linea(auxString));

        id->addKey(new FranjaHoraria(rand()));

        auxString.clear();
        stringSize = rand() % 15 + 5;
        for (int i = 0; i < stringSize; ++i)
            auxString += rand() % 25 + 65;
        id->addKey(new Falla(auxString));

        auxString.clear();
        stringSize = rand() % 15 + 10;
        for (int i = 0; i < stringSize; ++i)
            auxString += rand() % 25 + 65;
        id->addKey(new Accidente(auxString));

        id->addKey(new Formacion(rand() % 2048));

        return new Record(id);
    }

    void test_Full_NonSense_records()
    {
        start("Full_NonSense_records");

        blockSize = 256;
        path = "/tmp/test_Full.bin";
		spacePath = "/tmp/test_Full_space.bin";
        k = 5;

        FileBlocks * f = new FileBlocks(path, blockSize);
        KDtree * tree = new KDtree(k, f);
        KeyFactory::setDimensions(k);
        Record::setDimensions(k);
        std::vector<Record* > records(q);
        for (int i = 0; i < q; ++i)
            records[i] = getRand_NonSense_Record();

        tree->load(records);
        tree->dump();

        cleanUp();
    }


};
