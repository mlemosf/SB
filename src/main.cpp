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
	printf("1\n");
	leitor->setInterfacesCount();
	leitor->setInterfaces();
	leitor->setFieldsCount();
	leitor->setFields();
	leitor->setMethodsCount();
	leitor->setMethods();
	printf("2\n");
	leitor->setAttributesCount();
	leitor->setAttributes();
	printf("3\n");
	Exibidor *ex = new Exibidor(*leitor);
	ex->Mostrar();

	

	delete(leitor);
	return 0;

}