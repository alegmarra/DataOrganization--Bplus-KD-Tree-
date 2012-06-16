#ifndef INPUT_PARSER_CPP_
#define INPUT_PARSER_CPP_

#include "Exceptions/FileErrorException.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include <sstream>

#include "KDTree/RecordID/ID.h"
#include "KDTree/RecordID/IntKey.h"
#include "KDTree/Record.h"

#include <time.h>
#include "KDTree/RecordID/KeyFactory.h"
#include "KDTree/RecordID/Linea.h"
#include "KDTree/RecordID/FranjaHoraria.h"
#include "KDTree/RecordID/Falla.h"
#include "KDTree/RecordID/Accidente.h"
#include "KDTree/RecordID/Formacion.h"
#include "KDTree/RecordID/KeyFactory.h"

class InputParser {


private:

	static std::vector< std::vector<std::string> > recoverField(const char * path){

		std::string line;
		std::vector<std::string> field;
		std::vector< std::vector<std::string> > records;

		std::ifstream inFile(path, std::ifstream::in);

		if(!inFile.good())
			throw new FileErrorException("Error opening input text file", 0);

		getline (inFile,line);

		while (!inFile.eof() && (line != "")){

			char chr;
			unsigned indx = 0;
			chr = line[indx];
			field.clear();

			while (indx < line.size()){

				if (chr == '['){
					std::string word;
					indx++;
					chr = line[indx];

					do{
					   word = word + chr;
					   indx++;
					   chr = line[indx];
					}while (chr != ']');

					field.push_back(word);
				}
				indx++;
				chr = line[indx];
			}
			records.push_back(field);
			getline (inFile,line);
		}

		inFile.close();

		return records;
	}

public:

	static std::vector<Record*> recoverRecords(const char * path){


		std::vector< std::vector<std::string> > inputRecords = InputParser::recoverField(path);

		if (inputRecords.size() == 0)
			throw new FileErrorException("Empty File", 0);

		std::vector<Record*> records;

		int dimensions = inputRecords[0].size();

		srand(time(NULL));

		for (unsigned i = 0; i < inputRecords.size(); i++){

			std::vector<std::string> set = inputRecords[i];

			ID* id = new ID(dimensions);

			id->addKey(LINEA, KeyFactory::getKey(LINEA, set[0]));
			//id->addKey(FRANJA, KeyFactory::getKey(FRANJA, set[0]);
			id->addKey(new FranjaHoraria(atoi(set[4].c_str())));
			id->addKey(FALLA, KeyFactory::getKey(FALLA, set[1]));
			id->addKey(ACCIDENTE, KeyFactory::getKey(ACCIDENTE, set[2]));
			id->addKey(FORMACION, KeyFactory::getKey(FORMACION, set[3]));
/*
		    id->addKey(new Linea(set[0]));
            id->addKey(new FranjaHoraria(atoi(set[4].c_str())));
		    id->addKey(new Falla(set[1]));
		    id->addKey(new Accidente(set[2]));
		    id->addKey(new Formacion(atoi(set[3].c_str())));
*/
	        records.push_back( new Record(id));

		}

		return records;
	}

};

#endif
