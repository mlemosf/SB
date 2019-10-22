#include <iostream>
#include "../include/leitor.hpp"
#include "../include/exibidor.hpp"
using namespace std;

int main(int argc, char ** argv) {
	Leitor *leitor = new Leitor();

	char* filename = argv[1];

	leitor->loadFile(filename);
	leitor->setMagicNumber();
	leitor->setMinorVersion();
	leitor->setMajorVersion();
	leitor->setConstantPoolCount();
	leitor->setConstantPool();

	leitor->setAccessFlags();
	leitor->setThisClass();
	leitor->setSuperClass();

	leitor->setInterfacesCount();
	// leitor->setInterfaces();
	leitor->setFieldsCount();
	// leitor->setFields();
	leitor->setMethodsCount();
	leitor->setMethods();
	leitor->setAttributesCount();
	//leitor->setAttributes();

	leitor->exibir();

	delete(leitor);
	return 0;

}