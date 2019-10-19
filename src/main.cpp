#include <iostream>
#include "../include/leitor.hpp"
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

	leitor->exibir();

	delete(leitor);
	return 0;

}