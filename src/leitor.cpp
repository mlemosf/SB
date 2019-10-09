#include "../include/leitor.hpp"
using namespace std;

void Leitor::loadFile(const string filename) {
	ifstream classfile;
	classfile.open(filename, ios::in|ios::binary);

	classfile.seekg(0, ios::end);
	int32_t filesize = classfile.tellg();

	char buffer;
	unsigned char *fileContent = new unsigned char[filesize];
	classfile.seekg(0, ios::beg);
	
	if (classfile.is_open()) {
		int32_t i = 0;
		while(!classfile.eof()) {
			classfile.read(&buffer, 1);
			fileContent[i] = static_cast<unsigned char>(buffer);
			i++;
		}
	}
	else {
		printf("Unable to open file\n");
	};
	this->byteArray = fileContent;
}

void Leitor::setMagicNumber() {
	int32_t size = 4;
	int32_t buffer[size];
	unsigned char magic[size];
	int j = size - 1;
	for (int i = 0; i < size; i++) {
		magic[j]= *(this->byteArray + i);
		j--;
	}

	memcpy(buffer, &magic, sizeof magic); 
	if (*buffer == (int32_t)0xcafebabe)  {
		this->magic = *buffer;
	}
	else {
		printf("Invalid class file\n");
	}
}