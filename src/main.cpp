#include <iostream>
#include "../include/leitor.hpp"
 #include "../include/Frame.hpp"
#include "../include/Heap.hpp"

#define EXECUTAR '1'
#define LEITOR '0'
using namespace std;


void showHelp() {
	printf("Execucão: ./main ARQUIVO OPCÃO\n");
	printf("opcões:\n");
	printf(" 0 (leitor/exibidor)\n");
	printf(" 1 (execucão)\n");
}

int main(int argc, char ** argv) {
	Leitor *leitor = new Leitor();

	if (argc <= 2) {
		showHelp();
		delete(leitor);
		return 0;
	}
	char* filename = argv[1];
	char option = *argv[2];
	bool validFile = false;
	leitor->loadFile(filename);
	validFile=leitor->set(MAGIC_NUMBER);
	if(validFile){
		leitor->set(MINOR_VERSION);
		leitor->set(MAJOR_VERSION);
		leitor->set(CONSTANT_POOL_COUNT);
		leitor->set(CONSTANT_POOL);
		leitor->set(ACCESS_FLAGS);
		leitor->set(THIS_CLASS);
		leitor->set(SUPER_CLASS);
		leitor->set(INTERFACES_COUNT);
		leitor->set(FIELDS_COUNT);
		leitor->set(FIELDS);
		leitor->set(METHODS_COUNT);
		leitor->set(METHODS);
		leitor->set(ATTRIBUTES_COUNT);

		if(option == EXECUTAR){
			Frame::setOpcodes();
			Heap *hp;
			hp = Heap::getInstance();
			hp->runMain(leitor);
			// printf("Main:: rodou o hp->runMain()\n"); // printou isso
			delete(hp);
			// printf("Deletou o hp\n"); // não printou isso
		} else {
			leitor->exibir();
		}
	}

	// printf("Deletar leitor\n");
	delete(leitor);
	// printf("Deletou leitor\n");
	return 0;

}
