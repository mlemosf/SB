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

enum ReturnTypesKey{
	MAGIC_NUMBER,
	MINOR_VERSION,
	MAJOR_VERSION,
	CONSTANT_POOL_COUNT,
	CONSTANT_POOL,
	ACCESS_FLAGS,
	THIS_CLASS,
	SUPER_CLASS,
	INTERFACES_COUNT,
	INTERFACES,
	FIELDS,
	FIELDS_COUNT,
	METHODS,
	METHODS_COUNT,
	ATTRIBUTES_COUNT,
	ATTRIBUTES
};
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
		u2 access_flags; //OK
		u2 this_class; //OK
		u2 super_class;//OK
		u2 interfaces_count;//OK
		u2 * interfaces; // OK
		u2 fields_count; //  OK
		vector<Field_info> fields;// Faltando
		u2 methods_count; // 
		Method_info methods; // Faltando
		u2 attributes_count; // 
		vector< Attribute_info> attributes; // Faltando

		u4 current_size;	// atributo não oficial, guarda a posicão atual de memória
		bool setMagicNumber();
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
	public:
		unsigned char* byte_array;
		void loadFile(string filename);
		void exibir();
		
		bool set(int key);
		u2 get(int key);
		u4 getMagicNumber();
		vector<Field_info> getFields();
		vector<Method_info> getMethods();
		u2 * getInterfaces();
		vector<Attribute_info> getAttributes();
		
		// bool setAccessFlagCount();

		void printAccessFlags();
		void printThisClass();
		void printSuperClass();
		void printInterfaceCont();
		void printInterfaces();
		void printFieldsCount();
		u1 read1byte();
		u2 read2byte();
		u4 read4byte();
};

#endif