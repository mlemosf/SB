#include <iostream>
#include "../include/leitor.hpp"
using namespace std;
int main(int argc, char ** argv) {
	Leitor *leitor = new Leitor();

	char* filename = argv[1];

	leitor->loadFile(filename);
	/*leitor->setMagicNumber();
	leitor->setMinorVersion();
	leitor->setMajorVersion();
	leitor->setConstantPoolCount();
	leitor->setConstantPool();
	leitor->setAccessFlags();
	leitor->exibir();


	leitor->setThisClass();
	leitor->setSuperClass();
	leitor->setInterfacesCount();
	leitor->setInterfaces();
	leitor->setFieldsCount();
	leitor->setFields();
	leitor->printAccessFlags(); 
	leitor->printThisClass();
	leitor->printSuperClass();
	leitor->printInterfaceCont();
	leitor->printInterfaces();
	leitor->printFieldsCount();
	*/// leitor->setFields();
	//leitor->setMethodsCount();
	// leitor->setMethods();
	//leitor->setAttributesCount();
	// leitor->setAttributes();
	

	delete(leitor);
	return 0;

}