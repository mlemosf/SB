#ifndef CPINFO_H
#define CPINFO_H

#include <cstdint>
#include <iostream>
#include <vector>

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType  16
#define CONSTANT_InvokeDynamic 18

using namespace std;

class CONSTANT_Class_info {
	public:
		u1 tag;
		u2 name_index;
};

class CONSTANT_Methodref_info {
	public:
		u1 tag;
		u2 class_index;
		u2 name_and_type_index;
};

class CONSTANT_Fieldref_info {
	public:
		u1 tag;
		u2 class_index;
		u2 name_and_type_index;
};

class CONSTANT_InterfaceMethodref_info {
	public:
		u1 tag;
		u2 class_index;
		u2 name_and_type_index;
};

class CONSTANT_String_info {
	public:
		u1 tag;
		u2 string_index;
};

class CONSTANT_Integer_info {
	public:
		u1 tag;
		u4 bytes;
};

class CONSTANT_Float_info {
	public:
		u1 tag;
		u4 bytes;
};

class CONSTANT_Long_info {
	public:
		u1 tag;
		u4 high_bytes;
		u4 low_bytes;
};

class CONSTANT_Double_info {
	public:
		u1 tag;
		u4 high_bytes;
		u4 low_bytes;
};

class CONSTANT_NameAndType_info {
	public:
		u1 tag;
		u2 name_index;
		u2 descriptor_index;
};

class CONSTANT_Utf8_info {
	public:
		u1 tag;
		u2 length;
		u1 bytes[];
};

class CONSTANT_MethodHandle_info {
	public:
		u1 tag;
		u1 reference_kind;
		u2 reference_index;
};

class CONSTANT_MethodType_info {
	public:
		u1 tag;
		u2 descriptor_index;
};

class CONSTANT_InvokeDynamic_info {
	public:
    	u1 tag;
    	u2 bootstrap_method_attr_index;
    	u2 name_and_type_index;
};


union cp_info_element {
	CONSTANT_Class_info c1;
	CONSTANT_Methodref_info c2;
	CONSTANT_Fieldref_info c3;
	CONSTANT_InterfaceMethodref_info c4;
	CONSTANT_String_info c5;
	CONSTANT_Integer_info c6;
	CONSTANT_Float_info c7;
	CONSTANT_Long_info c8;
	CONSTANT_Double_info c9;
	CONSTANT_NameAndType_info c10;
	CONSTANT_Utf8_info c11;
	CONSTANT_MethodHandle_info c12;
	CONSTANT_MethodType_info c13;
	CONSTANT_InvokeDynamic_info c14;
};


class Cp_info {
	private:
		// colocar aqui a estrutura que vai guardar 
		// os elementos do constant pool
		vector<cp_info_element> constant_pool;
	public:
		u4 getConstantPoolTag(u2 tag, u4 size);

};

#endif