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

    #ifndef DIMENSIONS
	#define DIMENSIONS 5
	#endif

  
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
    
    void findAction() 
    {
        if (path.size() == 0 || args.size() == 0) {
            usageAction();
            return;
        }
        
        Query * q = new Query();

        for (int i = 0; i < args.size(); i++) {
            std::string dimension = "";
            char op = 'M'; // (E)qual, (R)ange, (F)inished or (M)issing
            std::string low = "";
            std::string high = "";
            char status = 'D'; // (D)imension, (L)ow or (H)igh
            std::string * container = &dimension;           
            for (int c = 0; c < args[i].size(); c++) {
                char _c = args[i][c];
                switch(status) {
                    case 'D':
                        if (_c == '=' || _c == '[') {
                            if (_c == '=') {
                                op = 'E';
                            } else {
                                op = 'R';
                            }
                            container = &low;
                            status = 'L';
                        } else {
                            (*container) += _c;
                        }
                        break;
                        
                    case 'L':
                        if (_c == ',') {
                            container = &high;
                            status = 'H';
                        } else {
                            (*container) += _c;
                        }
                        break;
                        
                    case 'H':
                        if (_c == ']') {
                            status = 'F';
                        } else {
                            (*container) += _c;
                        }
                        break;
                        
                    default: break;
                }
                
            }
            
            std::cout << "Dimension: " << dimension << std::endl;
            std::cout << "Operador: " << op << std::endl;
            std::cout << "Low: " << low << std::endl;
            std::cout << "High: " << high << std::endl;
        }        
    };
    
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

