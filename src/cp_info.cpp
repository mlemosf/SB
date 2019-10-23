#include "../include/cp_info.hpp"
using namespace std;

void Cp_info::concatBytes(u1* buffer, u2 size, u1* bytes) {
	int32_t j = 0;
	for (int32_t i = 3; i < size + 1; i++) {
		bytes[j] = *(buffer + i);
		j++;
	}
	printf("\n");
}


u4 Cp_info::getConstantPoolTag(u2 tag, u4 utf8_size) {
	int32_t size = 0;

	switch (tag) {
		case CONSTANT_Class:
			size = sizeof(CONSTANT_Class_info);
			break;
		case CONSTANT_Fieldref:
			size = sizeof(CONSTANT_Fieldref_info);
			break;
		case CONSTANT_Methodref:
			size = sizeof(CONSTANT_Methodref_info);
			break;
		case CONSTANT_InterfaceMethodref:
			size = sizeof(CONSTANT_InterfaceMethodref_info);
			break;
		case CONSTANT_String:
			size = sizeof(CONSTANT_String_info);
			break;
		case CONSTANT_Integer:
			size = sizeof(CONSTANT_Integer_info);
			break;
		case CONSTANT_Float:
			size = sizeof(CONSTANT_Float_info);
			break;
		case CONSTANT_Long:
			size = sizeof(CONSTANT_Long_info);
			break;
		case CONSTANT_Double:
			size = sizeof(CONSTANT_Double_info);
			break;
		case CONSTANT_NameAndType:
			size = sizeof(CONSTANT_NameAndType_info);
			break;
		case CONSTANT_Utf8:
			size = sizeof(CONSTANT_Utf8_info) + utf8_size - 12;
			break;
		case CONSTANT_MethodHandle:
			size = sizeof(CONSTANT_MethodHandle_info);
			break;
		case CONSTANT_MethodType:
			size = sizeof(CONSTANT_MethodType_info);
			break;
		case CONSTANT_InvokeDynamic:
			size = sizeof(CONSTANT_InvokeDynamic_info);
			break;
		default:
			printf("Tipo de dado inválido\n");
			break;
	}
	if (size <= 0) {
		return size;
	}
	else {
		return size - 1;
	}
}

cp_info_element Cp_info::addElement(u2 tag, u4 size, u4 position, u4 currentSize, unsigned char* byte_array, vector<cp_info_element>* constant_pool) {
	uint8_t buffer[size];
	int8_t val;
	int32_t j = size - 1;
	cp_info_element element;

	for (int32_t i = 0; i < size; i++) {
		val = *(byte_array + currentSize + position);
		buffer[i] = val;
		// j--;
		position++;
	}

	switch (tag) {
		case CONSTANT_Class: {
			CONSTANT_Class_info *class_info = new CONSTANT_Class_info();
			class_info->tag = buffer[0];
			class_info->name_index = (buffer[1] << 16) + (buffer[2] << 8);
			element.c1 = class_info;
			break;
		}
		case CONSTANT_Fieldref: {
			CONSTANT_Fieldref_info *fieldref_info = new CONSTANT_Fieldref_info();
			fieldref_info->tag = buffer[0];
			fieldref_info->class_index = (buffer[1] << 16) + (buffer[2] << 8);
			fieldref_info->name_and_type_index = (buffer[3] << 16) + (buffer[4] << 8);
			// printf("tag: %x\n", fieldref_info->tag);
			// printf("class_index: %x\n", fieldref_info->class_index);
			// printf("name: %x\n", fieldref_info->name_and_type_index);
			break;
		}
		case CONSTANT_Methodref: {
			CONSTANT_Methodref_info *methodref_info = new CONSTANT_Methodref_info();
			methodref_info->tag = buffer[0];
			methodref_info->class_index = (buffer[1] << 16) + (buffer[2] << 8);
			methodref_info->name_and_type_index = (buffer[3] << 16) + (buffer[4] << 8);
			element.c2 = methodref_info;
			// printf("tag: %x\n", methodref_info->tag);
			// printf("class_index: %x\n", methodref_info->class_index);
			// printf("name: %x\n", methodref_info->name_and_type_index);
			break;
		}
		case CONSTANT_Utf8: {
			int16_t utf8_size = buffer[2] + buffer[1];
			CONSTANT_Utf8_info *utf8_info = new CONSTANT_Utf8_info();	
			utf8_info->tag = buffer[0];
			utf8_info->length = utf8_size;
			utf8_info->bytes = new uint8_t[utf8_size];
			concatBytes(buffer, utf8_info->length + 2, utf8_info->bytes);
			// printf("bytes: %x\n", utf8_info->bytes[0]);
			element.c11 = utf8_info;
			break;
		}

	}
	// return element;
	// constant_pool->push_back(element);
	// this->
}