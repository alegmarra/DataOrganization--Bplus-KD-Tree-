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

#ifndef DIMENSIONS
#define DIMENSIONS 5
#endif


class App
{
private:
    std::string path;
    std::string action;
    std::vector< std::string > args;

    std::map< std::string, unsigned > routes;
    std::map< std::string, unsigned > fields;

public:
	App() {
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
		fields["linea"] = LINEA;
		fields["franja"] = FRANJA;
		fields["falla"] = FALLA;
		fields["accidente"] = ACCIDENTE;
		fields["formacion"] = FORMACION;
	}

	void setPath(std::string _path) {
		path = _path;
	}

	void setAction(std::string _action) {
		action = _action;
	}

	void addArg(char* arg) {
		args.push_back(arg);
	}

	void run() {
		switch (routes[action]) {
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
		std::vector<Record*> records = InputParser::recoverRecords(
				args[0].c_str());
		unsigned dim = DIMENSIONS;
		KDtree* tree = new KDtree(dim, new FileBlocks(path.c_str(), 4096));
		int result = tree->load(records);
		if (result == 0)
			std::cout << "Los registros se cargaron correctamente!"
					<< std::endl;
		else
			std::cerr << "Se encontraron registros duplicados, fueron omitidos"
					<< std::endl;

		delete tree;
	};

	void fillMissingData(std::vector<bool> visited, ID*& id) {

		for (int i = 0; i < DIMENSIONS; i++) {
			if (!visited[i])
				switch (i) {

				case (LINEA): {
					id->addKey(new Linea(" "));
					visited[LINEA] = true;
					break;
				}

				case (FRANJA): {
					id->addKey(new FranjaHoraria(0));
					visited[FRANJA] = true;
					break;
				}

				case (FALLA): {
					id->addKey(new Falla(" "));
					visited[FALLA] = true;
					break;
				}

				case (ACCIDENTE): {
					id->addKey(new Accidente(" "));
					visited[ACCIDENTE] = true;
					break;
				}

				case (FORMACION): {
					id->addKey(new Formacion(0));
					visited[FORMACION] = true;
					break;
				}

				}
		}
	}


	void createID(std::vector<std::vector<std::string> >& recordsList, ID*& id,
				  std::vector<bool>& visited) {

		for (int i = 0; i < recordsList.size(); i++) {

			std::vector < std::string > set = recordsList[i];

			switch (fields[set[0]]) {

			case (LINEA): {
				id->addKey(new Linea(set[1]));
				visited[LINEA] = true;
				break;
			}

			case (FRANJA): {
				id->addKey(new FranjaHoraria(atoi(set[1].c_str())));
				visited[FRANJA] = true;
				break;
			}

			case (FALLA): {
				id->addKey(new Falla(set[1]));
				visited[FALLA] = true;
				break;
			}

			case (ACCIDENTE): {
				id->addKey(new Accidente(set[1]));
				visited[ACCIDENTE] = true;
				break;
			}

			case (FORMACION): {
				id->addKey(new Formacion(atoi(set[1].c_str())));
				visited[FORMACION] = true;
				break;
			}

			default:
				std::cerr << "Invalid Key" << std::endl;
				break;
			}

		}
	}

	std::vector < std::vector<std::string> > parseInput(){

		std::vector < std::string > field;
		std::vector < std::vector<std::string> > recordsList;
		int pair = 0;
		int indx = 0;
		char chr;

		while (pair < args.size()) {
			std::string line = args[pair];
			int indx = 0;
			while (indx < line.size()) {
				std::string word;
				chr = line[indx];
				do {
					word += chr;
					indx++;
					chr = line[indx];
				} while ((chr != '=') && (indx < line.size()));
				field.push_back(word);
				indx++;
			}

			recordsList.push_back(field);
			field.clear();
			pair++;
		}

		return recordsList;
	}

	void insertAction() {

		std::vector < std::vector<std::string> > fieldsList = parseInput();

		Record* record;
		ID* id = new ID(DIMENSIONS);
		std::vector<bool> visited(DIMENSIONS, false);

		createID(fieldsList, id, visited);

		fillMissingData(visited, id);

        record = new Record(id);

        KDtree* tree = new KDtree(DIMENSIONS, new FileBlocks(path.c_str(), 4096));
        tree->insert(record);

        delete tree;

    };
    
    void findAction() 
    {
        std::cout << path;
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

