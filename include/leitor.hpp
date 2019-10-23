#ifndef LEITOR_H
#define LEITOR_H

#include <cstdlib>
// #include <iostream>
// #include <cstdint>
#include <fstream>
#include <string>
#include <string.h>
#include "cp_info.hpp"
#include "method_info.hpp"
#include "field_info.hpp"


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
		//cp_info constant_pool[constant_pool_count - 1];
		u2 access_flags;
		u2 this_class;
		u2 super_class;
		u2 interfaces_count;
		u2 interfaces;
		// u2 interfaces[interfaces_count];
		u2 fields_count;
		// field_info fields[fields_count];
		u2 methods_count;
		Method_info methods;
		u2 attributes_count;
		// attribute_info attributes[attributes_count];
		Attribute_info* attributes;

		u4 current_size;	// atributo não oficial, guarda a posicão atual de memória

	public:
		unsigned char* byte_array;
		void loadFile(string filename);
		bool setMagicNumber();
		void exibir();
		bool setMinorVersion();
		bool setMajorVersion();
		bool setConstantPoolCount();
		bool setConstantPool();
		bool setAccessFlags();
		bool setThisClass();
		bool setSuperClass();

		bool setInterfacesCount();
		bool setInterfaces();
		bool setFieldsCount();
		bool setFields();
		bool setMethodsCount();
		bool setMethods();
		bool setAttributesCount();
		bool setAttributes();

		u4 getMagicNumber();
		u2 getInterfacesCount();
		u2 getMinorVersion();
		u2 getMajorVersion();
    	u2 getConstantPoolCount();
		u2 getFieldsCount();
		u2 getMethodsCount();
		u2 getAttributesCount();
		u2 getAcessFlags();
		u2 getThisClass();
		u2 getSuperClass();
		vector<Field_info> getFields();
		vector<Method_info> getMethods();
		//vector<interface> getInterfaces();
		vector<Attribute_info> getAttributes();
		// bool setAccessFlagCount();

		u1 read1byte();
		u2 read2byte();
		u4 read4byte();
};

#endif