#include "UnitTests/KeyTest.cpp"
#include "UnitTests/ConditionTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"
#include "UnitTests/NodeTest.cpp"
#include "UnitTests/KDTreeTest.cpp"
#include "InputParser.cpp"
#include "KDTree/KD.h"
#include "File/FileBlocks.h"


#include <map>
#include <vector>
#include <string>

/**
 * Front controller
 *
 * Accepted format is:
 *     run path action [arg1 [arg2 [arg3]]]
 */
 
#define TEST 1
#define LOAD 2
#define INSERT 3
#define FIND 4
#define REMOVE 5
#define CLEAR 6
#define DELETE 7
#define SHOW 8

 
class App
{
private:
    std::string path;
    std::string action;
    std::vector< std::string > args;

    std::map< std::string, unsigned > routes;

    #ifndef DIMENSIONS
	#define DIMENSIONS 5
	#endif

  
public:

    App() 
    {
        routes["test"] = TEST;
        routes["load"] = LOAD;
        routes["insert"] = INSERT;
        routes["find"] = FIND; 
        routes["remove"] = REMOVE;
        routes["clear"] = CLEAR;
        routes["delete"] = DELETE;
        routes["show"] = SHOW;
    }

    void setPath(std::string _path)
    {
        path = _path;
    }

    void setAction(std::string _action)
    {
        action = _action;
    }
    
    void addArg(char * arg)
    {
        args.push_back(arg);
    }

    void run()
    {
        switch(routes[action]) {
            case LOAD:
                loadAction();
                break; 
            case INSERT:
                insertAction();
                break;
            case FIND:
                findAction();
                break;
            case REMOVE:
                removeAction();
                break; 
            case CLEAR:
                clearAction();
                break;
            case DELETE:
                deleteAction();
                break;
            case SHOW:
                showAction();
                break;
            case TEST:
                testAction();
                break;
            default:
                usageAction();
                break;
        }
    }

private:    
    void loadAction() {

        std::vector<Record* > records = InputParser::recoverRecords(args[0].c_str());

    	unsigned dim = DIMENSIONS;

        KDtree * tree = new KDtree(dim, new FileBlocks(path.c_str(), 4096));

        int result = tree->load(records);

        if (result == 0)
        	std::cout << "Loaded Successfully!" << std::endl;
        else
        	std::cerr << "Duplicated records on load, some records skipped" << std::endl;

        delete tree;

    };
    
    void insertAction() {};
    
    void findAction() {};
    
    void removeAction() {};
    
    void clearAction() {

    	unsigned dim = DIMENSIONS;

        KDtree * tree = new KDtree(dim, new FileBlocks(path.c_str(), 4096));

        tree->clear();

        delete tree;

    };
    
    void deleteAction() {

    	remove(path.c_str());

		std::string s = path;
		std::string listPath = s.substr(0, (s.size() -4));

		listPath += "_space.bin";

		remove(listPath.c_str());
    };
    
    void showAction() {

    	unsigned dim = DIMENSIONS;

        KDtree * tree = new KDtree(dim, new FileBlocks(path.c_str(), 4096));

        tree->dump();

        delete tree;
    };
 
    void testAction()
    {
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

    
    }
    
    void usageAction() 
    {
        // aca tiramos las instrucciones de uso por pantalla
    }   
};
