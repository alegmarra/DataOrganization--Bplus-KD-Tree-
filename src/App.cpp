#include "UnitTests/KeyTest.cpp"
#include "UnitTests/ConditionTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"
#include "UnitTests/NodeTest.cpp"
#include "UnitTests/KDTreeTest.cpp"

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
    void loadAction() {};
    
    void insertAction() {};
    
    void findAction() {};
    
    void removeAction() {};
    
    void clearAction() {};
    
    void deleteAction() {};
    
    void showAction() {};
 
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
