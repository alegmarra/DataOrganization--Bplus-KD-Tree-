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
 *     run <action> [<args>]
 */
 
#define TEST 1
#define LOAD 2
#define INSERT 3
#define FIND 4
#define REMOVE 5
#define CLEAR 6
#define DELETE 7
#define SHOW 8
#define HELP 9

 
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
        action = "";
        routes["test"] = TEST;
        routes["load"] = LOAD;
        routes["insert"] = INSERT;
        routes["find"] = FIND; 
        routes["remove"] = REMOVE;
        routes["clear"] = CLEAR;
        routes["delete"] = DELETE;
        routes["show"] = SHOW;
        routes["help"] = HELP;
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
            case HELP:
                helpAction();
                break;
            default:
                usageAction();
                break;
        }
    }

private:    
    void loadAction() {};
    
    void insertAction() {};
    
    void findAction() 
    {
        std::cout << path;
    };
    
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
        std::cout << "uso: run <comando> [<ruta> [<args>]]" << std::endl
            << std::endl
            << "La lista completa de comandos es:" << std::endl
            << "\ttest\t\tCorre las pruebas de unidad"  << std::endl
            << "\tload\t\tVuelca un archivo de texto en el árbol" << std::endl
            << "\tinsert\t\tInserta un nuevo elemento en el árbol" << std::endl
            << "\tfind\t\tRealiza una consulta sobre el árbol" << std::endl
            << "\tremove\t\tElimina un registro del árbol" << std::endl
            << "\tclear\t\tVacía el contenido del árbol" << std::endl
            << "\tdelete\t\t???" << std::endl
            << "\tshow\t\tMuestra el contenido del árbol" << std::endl
            << std::endl
            << "Probá 'run help <comando>' para mas información sobre un comando específico" << std::endl
            ;
    }
    
    
    
       
    void helpAction()
    {
        std::cout << "Para! quien te pensas que soy? Juan Carlos Manual?" << std::endl;
    }
};

