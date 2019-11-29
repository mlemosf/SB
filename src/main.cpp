#include <iostream>
#include "../include/leitor.hpp"
#include "../include/Frame.hpp"
using namespace std;
int main(int argc, char ** argv) {
	bool EXECUTAR = true;
	Leitor *leitor = new Leitor();

	char* filename = argv[1];

	leitor->loadFile(filename);
	leitor->set(MAGIC_NUMBER);
	leitor->set(MINOR_VERSION);
	leitor->set(MAJOR_VERSION);
	leitor->set(CONSTANT_POOL_COUNT);
	leitor->set(CONSTANT_POOL);
	leitor->set(ACCESS_FLAGS);
	leitor->set(THIS_CLASS);
	leitor->set(SUPER_CLASS);
	leitor->set(INTERFACES_COUNT);
	leitor->set(FIELDS_COUNT);
	// leitor->set(FIELDS);
	leitor->set(METHODS_COUNT);
	leitor->set(METHODS);
	// leitor->set(METHODS);
	// leitor->set(ATTRIBUTES_COUNT);
	// leitor->set(ATTRIBUTES);

	if(EXECUTAR){
		Frame::setOpcodes();
	} else {
		leitor->exibir();
	}
	delete(leitor);
	return 0;

}