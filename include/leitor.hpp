#ifndef LEITOR_H
#define LEITOR_H

#include <cstdlib>
// #include <iostream>
// #include <cstdint>
#include <fstream>
#include <string>
#include <string.h>
#include "cp_info.hpp"
#include "field_info.hpp"
#include "method_info.hpp"

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
		Cp_info *constant_pool;
		u2 access_flags;
		u2 this_class;
		u2 super_class;
		u2 interfaces_count;
		u2 interfaces;
		u2 fields_count;
		// field_info fields[fields_count];
		u2 methods_count;
		Method_info methods;
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
		bool setAccessFlags();
		bool setThisClass();
		bool setSuperClass();

		bool setInterfacesCount();
		u2 getInterfacesCount();
		bool setInterfaces();
		bool setFieldsCount();
		u2 getFieldsCount();
		bool setFields();
		bool setMethodsCount();
		u2 getMethodsCount();
		bool setMethods();
		u2 getAttributesCount();
		bool setAttributesCount();
		bool setAttributes();
		// bool setAccessFlagCount();
};

#endif