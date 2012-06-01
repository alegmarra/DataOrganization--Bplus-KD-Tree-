#include "UnitTests/KeyTest.cpp"
#include "UnitTests/ConditionTest.cpp"
#include "UnitTests/QueryTest.cpp"
#include "UnitTests/FileBlocksTest.cpp"
#include "UnitTests/SerializersTest.cpp"
#include "UnitTests/NodeTest.cpp"
#include "UnitTests/KDTreeTest.cpp"
#include "InputParser.cpp"
#include "../KDTree/KD.h"


/**
 * Front controller
 *
 * Accepted format is:
 *     run path action [arg1 [arg2 [arg3]]]
 */
class App
{
private:
    std::string action;
    std::vector< std::string > args;
    
    KDtree* appTree;


public:

    void setPath(std::string _path)
    {
    
    }

    void setAction(std::string _action)
    {
        action = _action;
    }
    
    void setArgs(std::string _args)
    {
        // Logica para separar los argumentos e insertarlos en el vector
        // si se pueden pasar desde main como array o algo asi, mejor
        args = _args;
    }

    void run()
    {
        switch(action) {
            "load":
                loadAction();
                break; 
            "insert":
                insertAction();
                break;
            "find":
                findAction();
                break;
            "remove":
                removeAction();
                break; 
            "clear":
                clearAction();
                break;
            "delete":
                deleteAction();
                break;
            "show":
                showAction();
                break;
            "test":
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
    
    void removeAction() {};
    
    void clearAction() {};
    
    void deleteAction() {};
    
    void showAction() {

    	appTree->dump();

    	//DELETE?????
    };
 
    void testAciton()
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
}
