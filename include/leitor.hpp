#ifndef LEITOR_H
#define LEITOR_H

#include <cstdlib>
// #include <iostream>
// #include <cstdint>
#include <fstream>
#include <string>
#include <string.h>
#include "cp_info.hpp"


// #define u1 uint8_t
// #define u2 uint16_t
// #define u4 uint32_t
using namespace std;

class Leitor {
	private:
		u4 magic;
		u2 minor_version;
		u2 major_version;
		u2 constant_pool_count;
		// cp_info constant_pool[constant_pool_count - 1];
		u2 access_flags;
		u2 this_class;
		u2 super_class;
		u2 interfaces_count;
		// u2 interfaces[interfaces_count];
		u2 fields_count;
		// field_info fields[fields_count];
		u2 methods_count;
		// method_info methods[methods_count];
		u2 attributes_count;
		// attribute_info attributes[attributes_count];

		u4 current_size;	// atributo não oficial, guarda a posicão atual de memória

	public:
		unsigned char* byte_array;
		void loadFile(string filename);
		bool setMagicNumber();
		u4 getMagicNumber();
		void exibir();
		bool setMinorVersion();
		u2 getMinorVersion();
		bool setMajorVersion();
		u2 getMajorVersion();
		bool setConstantPoolCount();
		u2 getConstantPoolCount();
		bool setConstantPool();
		
		// bool setAccessFlagCount();
};

#endif