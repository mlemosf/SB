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
		u4 getConstantPoolEntry(u2 tag);

};

#endif