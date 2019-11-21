#include <iostream>
#include "../include/leitor.hpp"
using namespace std;

int main(int argc, char ** argv) {
	Leitor *leitor = new Leitor();

	char* filename = argv[1];
	u2 * interfaces;

	leitor->loadFile(filename);
	leitor->setMagicNumber();
	leitor->setMinorVersion();
	leitor->setMajorVersion();
	leitor->setConstantPoolCount();
	leitor->exibir();
	leitor->setConstantPool();
	leitor->setAccessFlags();
	leitor->setThisClass();
	leitor->setSuperClass();
	leitor->setInterfacesCount();
	leitor->setInterfaces();
	leitor->setFieldsCount();
	leitor->printAccessFlags(); 
	leitor->printThisClass();
	leitor->printSuperClass();
	leitor->printInterfaceCont();
	leitor->printInterfaces();
	leitor->printFieldsCount();
	//leitor->setFieldsCount();
	// leitor->setFields();
	//leitor->setMethodsCount();
	// leitor->setMethods();
	//leitor->setAttributesCount();
	// leitor->setAttributes();
	

	delete(leitor);
	return 0;

}