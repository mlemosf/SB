#include "../include/cp_info.hpp"
using namespace std;

u4 Cp_info::getConstantPoolTag(u2 tag, u4 utf8_size) {
	// Definicão da funcão que define o elemento
	// que vai ser adicionado ao constant pool
	// printf("tag:  %d\n", tag);
	// int32_t tag2 = 7;
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
			size = sizeof(CONSTANT_Utf8_info) + utf8_size;
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
			// printf("Tipo de dado inválido\n");
			break;
	}
	// printf("%d\n" ,size);
	return size - 1;
}

void CONSTANT_Class_info::print()				{ printf("Tag: Class || Name index: %d\n", name_index) }
void CONSTANT_Methodref_info::print()			{ printf("Tag: Methodref || Class index: %d || Name and type index: %d\n", class_index, name_and_type_index) }
void CONSTANT_Fieldref_info::print()			{ printf("Tag: Fieldref || Class index: %d || Name and type index: %d\n", class_index, name_and_type_index) }
void CONSTANT_InterfaceMethodref_info::print()	{ printf("Tag: InterfaceMethodref || Class index: %d || Name and type index: %d\n", class_index, name_and_type_index) }
void CONSTANT_String_info::print()				{ printf("Tag: String || String index: %d\n", string_index) }
void CONSTANT_Integer_info::print()				{ printf("Tag: Integer || Bytes: %d\n", bytes) }
void CONSTANT_Float_info::print()				{ printf("Tag: Float || Bytes: %d\n", bytes) }
void CONSTANT_Long_info::print()				{ printf("Tag: Long || High bytes: %d || Low bytes: %d\n", high_bytes, low_bytes) }
void CONSTANT_Double_info::print()				{ printf("Tag: Double || High bytes: %d || Low bytes: %d\n", high_bytes, low_bytes) }
void CONSTANT_NameAndType_info::print()			{ printf("Tag: NameAndType || Name index: %d || Descriptor index: %d\n", name_index, descriptor_index) }
void CONSTANT_Utf8_info::print()				{ printf("Tag: Utf8 || Length: %d || Bytes[]: %d\n", length, bytes[0]) }
void CONSTANT_MethodHandle_info::print()		{ printf("Tag: MethodHandle || Reference kind: %d || Reference index: %d\n", reference_kind, reference_index) }
void CONSTANT_MethodType_info::print()			{ printf("Tag: MethodType || Descriptor index: %d\n", descriptor_index) }
void CONSTANT_InvokeDynamic_info::print()		{ printf("Tag: InvokeDynamic || Bootstrap Method Attributes Index: %d || Name and type index: %d\n", bootstrap_method_attr_index, name_and_type_index) }