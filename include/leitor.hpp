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
		u4 magic; // OK
		u2 minor_version; //OK
		u2 major_version; //OK
		u2 constant_pool_count; //OK
		Cp_info *constant_pool; //OK-
		u2 access_flags; //OK-
		u2 this_class; //OK
		u2 super_class;//OK
		u2 interfaces_count;//OK
		u2 * interfaces; // OK--
		u2 fields_count; //  OK
		vector<Field_info> fields;// Faltando
		u2 methods_count; // OK-
		Method_info methods; // Faltando
		u2 attributes_count; // OK-
		vector< Attribute_info> attributes; // Faltando

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
		u2 getAccessFlags();
		u2 getThisClass();
		u2 getSuperClass();
		vector<Field_info> getFields();
		vector<Method_info> getMethods();
		u2 * getInterfaces();
		vector<Attribute_info> getAttributes();
		// bool setAccessFlagCount();

		u1 read1byte();
		u2 read2byte();
		u4 read4byte();
};

#endif