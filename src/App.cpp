#ifndef APP_CPP
#define APP_CPP


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
#include "KDTree/Query/Builder.h"


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
#define REPORT 10

#ifndef DIMENSIONS
#define DIMENSIONS 5
#endif

#ifndef BLOCKSIZE
#define BLOCKSIZE 512
#endif


class App
{
private:
    std::string path;
    std::string action;
    std::vector< std::string > args;

    std::map< std::string, unsigned > routes;
    std::map< std::string, unsigned > fields;

    unsigned blockSize;
public:
    App() 
    {
        action = "";
        
        blockSize = 512;

        KeyFactory::setDimensions(DIMENSIONS);
        
        routes["test"] = TEST;
        routes["load"] = LOAD;
        routes["insert"] = INSERT;
        routes["find"] = FIND; 
        routes["remove"] = REMOVE;
        routes["clear"] = CLEAR;
        routes["delete"] = DELETE;
        routes["show"] = SHOW;
        routes["help"] = HELP;
        routes["report"] = REPORT;

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
		case REPORT:
			reportAction();
			break;
		default:
			usageAction();
			break;
		}
	}

private:
	void loadAction() {
		std::vector<Record*> records = InputParser::recoverRecords(	args[0].c_str());
		unsigned dim = DIMENSIONS;
		KDtree* tree = new KDtree(dim, new FileBlocks(path.c_str(), blockSize));
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
				if(line[indx] == '"')
					indx++;

			}

			recordsList.push_back(field);
			field.clear();
			pair++;
		}

		return recordsList;
	}

	Record* getRecordFromInput(){
		std::vector < std::vector<std::string> > fieldsList = parseInput();

		ID* id = new ID(DIMENSIONS);
		std::vector<bool> visited(DIMENSIONS, false);

		createID(fieldsList, id, visited);

		fillMissingData(visited, id);

		return new Record(id);
	}

	void insertAction() {

		Record* record = getRecordFromInput();

        KDtree* tree = new KDtree(DIMENSIONS, new FileBlocks(path.c_str(), blockSize));
        int result = tree->insert(record);

		if (result == 0)
			std::cout << "Registro cargado correctamente!"
					<< std::endl;
		else
			std::cerr << "Registro duplicado"
					<< std::endl;

        delete tree;

    };
    
    void findAction() 
    {
        if (path.size() == 0 || args.size() == 0) {
            usageAction();
            return;
        }
        
        QueryBuilder builder;
        Query * q = new Query();
        builder.setQuery(q);

        for (int i = 0; i < args.size(); i++) {
            
            bool parsed = builder.parse(args[i]);
            
            if (!parsed) {
                delete q;
                std::cerr << "Error de sintaxis" << std::endl;
                return;
            }
        }
        
        KDtree * tree = new KDtree(DIMENSIONS, new FileBlocks(path.c_str(), BLOCKSIZE));
        std::vector< Record * > result = tree->find(q);

        std::cout << "Se encontraron " << result.size() << " registros." << std::endl;
        
        for (int i = 0; i < result.size(); i++) {
            result[i]->dump();
            std::cout << std::endl;
        }
        
    };
    
    void removeAction() {

    	Record* record = getRecordFromInput();

        KDtree* tree = new KDtree(DIMENSIONS, new FileBlocks(path.c_str(), blockSize));
        int result= tree->remove(record);

		if (result == 0)
			std::cout << "Registro eliminado!"
					<< std::endl;
		else
			std::cerr << "Registro No encontrado"
					<< std::endl;

        delete tree;

    };
    
    void clearAction() {

        KDtree * tree = new KDtree(DIMENSIONS, new FileBlocks(path.c_str(), blockSize));

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

        KDtree * tree = new KDtree(DIMENSIONS, new FileBlocks(path.c_str(), blockSize));

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
    

    bool shown(Key* key,std::vector<Key*> shownKeys){

    	for(int i = 0; i< shownKeys.size(); i++){
    			try{
    				if(shownKeys[i]->compareTo(key) == 0)

    				return true;
    			}catch(InvalidKeyException& e){

    			}
    	}

    	return false;
    }

    void reportAction()
    {
    	/*
    	Todos los trenes que tienen cierta falla.
		Todos los trenes que tienen cierto accidente.
		Todas las fallas de una formacion determinada.
		Todos los accidentes de una formacion determinada.
		Todas las fallas.
		Todas las formaciones.
		Todas las lineas.
		Todos los accidentes
		*/
		
		std::map< std::string, unsigned > available_reports;
		
		available_reports["trenesxfalla"] = 1;
		available_reports["trenesxaccidente"] = 2;
		available_reports["fallasxformacion"] = 3;
		available_reports["accidentesxformacion"] = 4;
		available_reports["fallas"] = 5;
		available_reports["formaciones"] = 6;
		available_reports["lineas"] = 7;
		available_reports["accidentes"] = 8;
		
		if (args.size() == 0) {
			std::cerr << "No se especificó el tipo de reporte" << std::endl;
			return;
		}
		
		if (available_reports.find(args[0]) == available_reports.end()) {
			std::cerr << "No se encontró el reporte especificado" << std::endl;
			return;
		}
		
		Query * q = new Query();
		QueryBuilder builder;
		builder.setQuery(q);
		std::vector< std::string > headers;
		std::vector< unsigned > fields;
		
		switch (available_reports[args[0]]) {
			case 1:
				if (args.size() < 2) {
					std::cerr << "No se especificó la falla" << std::endl;
					delete q;
					return;				
				}
				
				builder.parse("falla=" + args[1]);
				
				headers.push_back("Línea");
				headers.push_back("Formación");
				
				fields.push_back(LINEA);
				fields.push_back(FORMACION);
				
				break;
			case 2:
				if (args.size() < 2) {
					std::cerr << "No se especificó el accidente" << std::endl;
					delete q;
					return;				
				}
				
				builder.parse("accidente=" + args[1]);
				
				headers.push_back("Línea");
				headers.push_back("Formación");
				
				fields.push_back(LINEA);
				fields.push_back(FORMACION);
				
				break;

			case 3:
				if (args.size() < 2) {
					std::cerr << "No se especificó la línea ni la formación" << std::endl;
					delete q;
					return;				
				}
				
				if (args.size() < 3) {
					std::cerr << "No se especificó la formación" << std::endl;
					delete q;
					return;				
				}
				
				builder.parse("linea=" + args[1]);
				builder.parse("formacion=" + args[2]);
				
				headers.push_back("Línea");
				headers.push_back("Formación");
				headers.push_back("Falla");
				
				fields.push_back(LINEA);
				fields.push_back(FORMACION);
				fields.push_back(FALLA);
				
				break;

			case 4:
				if (args.size() < 2) {
					std::cerr << "No se especificó la línea ni la formación" << std::endl;
					delete q;
					return;				
				}
				
				if (args.size() < 3) {
					std::cerr << "No se especificó la formación" << std::endl;
					delete q;
					return;				
				}
				
				builder.parse("linea=" + args[1]);
				builder.parse("formacion=" + args[2]);
				
				headers.push_back("Línea");
				headers.push_back("Formación");
				headers.push_back("Accidente");
				
				fields.push_back(LINEA);
				fields.push_back(FORMACION);
				fields.push_back(ACCIDENTE);
				
				break;
				
			case 5:
				headers.push_back("Falla");
				fields.push_back(FALLA);
				
				break;
			
			case 6:
				headers.push_back("Línea");
				headers.push_back("Formacion");
				fields.push_back(LINEA);
				fields.push_back(FORMACION);
				
				break;
				
			case 7:
				headers.push_back("Línea");
				fields.push_back(LINEA);
				
				break;
				
			case 8:
				headers.push_back("Accidente");
				fields.push_back(ACCIDENTE);
				
				break;
				
			default: 
				std::cerr << "Ha ocurrido un error" << std::endl;
				return;
		}
		
		KDtree * tree = new KDtree(DIMENSIONS, new FileBlocks(path.c_str(), blockSize));
		std::vector< Record * > result = tree->find(q);
		
		if (result.size() == 0) {
			std::cout << "No se encontraron registros" << std::endl;
		} else {
			std::cout << std::endl;

			for(int i = 0; i < headers.size(); i++) {
				std::cout << headers[i];
				std::cout << "\t\t";
			}
			
			std::cout << std::endl;
			std::cout << std::endl;
		
			std::vector<Key*> shownKeys;

			for (int i = 0; i < result.size(); i++) {
				for (int f = 0; f < fields.size(); f++) {
					if ((!shown(result[i]->getID()->getKey(fields[f]), shownKeys)) || (fields.size()>1)){
						result[i]->getID()->getKey(fields[f])->dump();
						shownKeys.push_back(result[i]->getID()->getKey(fields[f]));
						std::cout << "\t\t";
						if((fields.size()==1))std::cout << std::endl;
					}
				}
				if((fields.size()>1))std::cout << std::endl;
			}


		}
		
		delete tree;
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
            << "\tdelete\t\tBorra todos los archivos relacionados " << std::endl
            << "\tshow\t\tMuestra el contenido del árbol" << std::endl
            << "\treport\t\tMuestra los reportes" << std::endl
            << std::endl
            << "Probá 'run help <comando>' para mas información sobre un comando específico" << std::endl
            ;
    }
    
    
    
       
    void helpAction()
    {
        std::cout << "Para! quien te pensas que soy? Juan Carlos Manual?" << std::endl;
    }
};

#endif
