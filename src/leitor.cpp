#include "../include/leitor.hpp"
using namespace std;

char* Leitor::loadFile(const string filename) {
	ifstream classfile;
	classfile.open(filename, ios::in|ios::binary);

	classfile.seekg(0, ios::end);
	int filesize = classfile.tellg();

	char buffer;
	char *fileContent = new char[filesize];
	

	classfile.seekg(0, ios::beg);
	
	if (classfile.is_open()) {
		int i = 0;
		while(!classfile.eof()) {
			classfile.read(&buffer, 1);
			fileContent[i] = buffer;
			i++;
		}
		printf("\n");
	}
	else {
		printf("Unable to open file\n");
	}

	return fileContent;
}