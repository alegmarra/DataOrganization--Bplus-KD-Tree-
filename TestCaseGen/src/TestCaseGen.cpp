//============================================================================
// Name        : TestCaseGen.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, ANSI-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>


std::vector<std::string> recuperarCampos(std::string linea){

	std::vector<std::string> campos;
	char chr;
	unsigned indx = 0;

	chr = linea[indx];

	while (indx < linea.size()){

		if ((chr == '[') or (chr ==',')){

			std::string palabra;
			indx++;
			chr = linea[indx];

			do{
			   palabra = palabra + chr;
		   	   indx++;
			   chr = linea[indx];

			}while ((chr != ']') and (chr !=',') and (chr != '\000'));

			campos.push_back(palabra);
		}

		indx++;
		chr = linea[indx];

	}

    return campos;

}

int main(int argc, char* argv[]) {

	//Cantidad de registros de prueba generados
	unsigned cantReg;

	if (argc > 0) cantReg = *argv[0];
	else cantReg = 50;

	std::ifstream inFile("src/fuenteDB.txt");
	std::ofstream outFile("src/testData.txt");

	std::string linea;


	if (inFile.is_open() && outFile.is_open()){

		do{
			getline (inFile,linea);

			while (!inFile.eof() && (linea != ""))
			{
			   std::vector<std::string> campos;
			   std::vector<std::string>::iterator it;


	//		   std::cout << linea << std::endl;

			   campos = recuperarCampos(linea);

			   srand((time(NULL)));

			   unsigned random = (rand()%(campos.size()-1)+1);

			   outFile << campos[0] << ": " << campos[random] << ", ";
			   getline (inFile,linea);
			}

			srand ((time(NULL)));
			outFile << "Formacion: " << (rand() % 2000 +1) << "\n";

			sleep(3);

			cantReg--;

			if (cantReg >0){
				inFile.clear();
				inFile.seekg(0, std::ifstream::beg);
			}

		}while(cantReg>0);


		outFile.close();
		inFile.close();
	}
	else{
		std::cout << "FILES NOT FOUND";
	}


	return 0;
}
