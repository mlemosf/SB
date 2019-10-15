#ifndef CPINFO_H
#define CPINFO_H

#include <cstdint>

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

class CONSTANT_Methodref {
	public:
		u1 tag;
		u2 class_index;
		u2 name_and_type_index;
};

class Cp_info {
	private:
		// colocar aqui a estrutura que vai guardar 
		// os elementos do constant pool
	public:
		static const uint8_t CONSTANT_Class = 7;
		static const uint8_t CONSTANT_Fieldref = 9;
		static const uint8_t CONSTANT_Methodref = 10;
		static const uint8_t CONSTANT_InterfaceMethodref = 11;
		static const uint8_t CONSTANT_String = 8;
		static const uint8_t CONSTANT_Integer = 3;
		static const uint8_t CONSTANT_Float = 4;
		static const uint8_t CONSTANT_Long = 5;
		static const uint8_t CONSTANT_Double = 6;
		static const uint8_t CONSTANT_NameAndType = 12;
		static const uint8_t CONSTANT_Utf8 = 1;
		static const uint8_t CONSTANT_MethodHandle = 15;
		static const uint8_t CONSTANT_MethodType  = 16;
		static const uint8_t CONSTANT_InvokeDynamic = 18;
		 
		u4 getConstantPoolEntry(u2 tag);

};

#endif