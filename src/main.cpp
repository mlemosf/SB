#include <iostream>
#include "../include/leitor.hpp"
using namespace std;

int main(int argc, char ** argv) {
	// printf("%s\n", argv[1]);
	Leitor *leitor = new Leitor();

	char* filename = argv[1];

	char *file = leitor->loadFile(filename);
	printf("%08x\n", *(file));

	delete(leitor);
	return 0;

}