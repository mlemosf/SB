#include <iostream>
#include "../include/leitor.hpp"
using namespace std;

int main(int argc, char ** argv) {
	Leitor *leitor = new Leitor();

	char* filename = argv[1];

	leitor->loadFile(filename);
	leitor->setMagicNumber();

	delete(leitor);
	return 0;

}