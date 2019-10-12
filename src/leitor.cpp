#include "../include/leitor.hpp"
using namespace std;


/* LEITOR */

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
	this->byte_array = fileContent;
}

bool Leitor::setMagicNumber() {
	int32_t size = 4;
	int32_t buffer[size];
	unsigned char magic[size];
	int32_t j = size - 1;
	bool result  = false;

	for (int32_t i = 0; i < size; i++) {
		magic[j]= *(this->byte_array + i);
		j--;
	}

	memcpy(buffer, &magic, sizeof(magic));

	if (*buffer == (int32_t)0xcafebabe)  {
		this->magic = *buffer;
		result = true;
	}
	else {
		printf("Invalid class file\n");
	}
	this->current_size = sizeof(this->magic);
	return result;
}


bool Leitor::setMinorVersion() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t minor_version[size];

	for (int32_t i = 0; i < size; i++) {
		minor_version[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &minor_version, sizeof(minor_version));
	this->minor_version = *buffer;
	this->current_size += sizeof(this->minor_version);
	return true;
}

bool Leitor::setMajorVersion() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t major_version[size];

	for (int32_t i = 0; i < size; i++) {
		major_version[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &major_version, sizeof(major_version));
	this->major_version = *buffer;
	this->current_size += sizeof(this->major_version);
	return true;
}

bool Leitor::setConstantPoolCount() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t constant_pool_count[size];

	for (int32_t i = 0; i < size; i++) {
		constant_pool_count[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &constant_pool_count, sizeof(constant_pool_count));
	this->constant_pool_count = *buffer;
	this->current_size += sizeof(this->constant_pool_count);
	return true;
}

bool Leitor::setConstantPool() {

	return true;
}

/* EXIBIDOR */

void Leitor::exibir() {
	printf("Magic number: %x\n", this->magic);
	printf("Minor version: %x\n", this->minor_version);
	printf("Major version: %x\n", this->major_version);
}