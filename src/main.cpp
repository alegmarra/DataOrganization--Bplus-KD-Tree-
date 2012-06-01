#include "UnitTests/KeyTest.cpp"
#include "UnitTests/ConditionTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"
#include "UnitTests/NodeTest.cpp"
#include "UnitTests/KDTreeTest.cpp"

#include "KDTree/KD.h"
#include "InputParser.cpp"


int main(int argc, char * argv[])
{
	/*
	 * argv[0] -> treeFile path
	 * argv[1] -> acction: load   , insert, find, remove, clear
	 * argv[2] -> input: data path, , find, remove, clear
	 *
	 *
	 * actions - input_type:
	 *
	 * 		load   : dataPath || - [Linea: X, Falla: Y, ...];[];[]
	 * 		insert : [Linea: X, Falla: Y, ...]
	 * 		find   : Linea: =Sarmiento; Falla: [motores 20%, motores 80%]; Formacion: [1, 20]
	 * 		remove : [Linea: X, Falla: Y, ...]
	 * 		clear  :
	 */


	if(argc < 3)
		std::cout << "Wrong number of parameters: "<< argc << std::endl;

	else{

		int dimensions = 5;
		const char* filename = argv[1];
		KDtree* tree = new KDtree(dimensions, new FileBlocks(filename, 4096));

		std::string action = argv[2];

		if(action.compare("load")==0){

			if(4 <= argc){
				int result = tree->load(InputParser::recoverRecords(argv[3]));

				if (result == 0 )
					std::cout << "Successfull Load!" << std::endl;
				else{
					std::cout << "Records Loaded" << std::endl;
					std::cout << "At leas one duplicated record, record skipped" << std::endl;
				}

				delete tree;
			}
			else
				std::cout << "Invalid Input for Action" << std::endl;

		}else if (action.compare("show")==0){

			tree->dump();

		}else if (action.compare("insert")==0){



		}else if (action.compare("find")==0){

		    Query* q = new Query();
		    std::vector<std::string> fields(dimensions);
		    for(int i=3; i<argc; i++){

		    	std::string s = argv[i];


//NO DARLE BOLA; ERA PRUEBA
		    	if(s.compare("Linea")== 0)
				    q->addCondition(LINEA, new QueryCondition(new Linea(argv[i+1])));

		    	else
		    	if (s.compare("Falla")== 0)
		            q->addCondition(FALLA, new QueryCondition(new Falla(argv[i+1])));

		    	else
		    	if(s.compare("Accidente")== 0)
		            q->addCondition(ACCIDENTE, new QueryCondition(new Accidente(argv[i+1])));

		    }

		    q->addCondition(LINEA, new QueryCondition(new Linea("Mitre")));

	        std::vector<Record*> result = tree->find(q);

	        for (int i = 0; i< result.size(); i++)
	        	result[i]->dump();

            std::cout<< "Results Size" << result.size() << std::endl;
/////////////////////////////////////////
		}else if (action.compare("remove")==0){



		}else if (action.compare("clear")==0){

			tree->clear();
			delete tree;

		}else if (action.compare("delete")==0){

			remove(filename);
			std::string s = filename;
			std::string listPath = s.substr(0, (s.size() -4));

			listPath += "_space.bin";
			remove(listPath.c_str());

		}else{
			std::cout << "Invalid Action" << std::endl;
		}



	}//else

/*
	Test* test;

	test = new KeyTest();
	test->run();
	delete test;

    test = new ConditionTest();
    test->run();
    delete test;

    test = new QueryTest();
    test->run();
	delete test;

	test = new FileBlocksTest();
	test->run();
	delete test;

    test = new SerializersTest();
    test->run();
    delete test;

    test = new NodeTest();
    test->run();
    delete test;

    test = new KDTreeTest();
    test->run();
    delete test;
*/
    return 0;
}

