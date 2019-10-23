#include "../include/cp_info.hpp"
#include <typeinfo>
using namespace std;

void Cp_info::concatBytes(u1* buffer, u2 size, u1* bytes) {
	int32_t j = 0;
	for (int32_t i = 3; i < size + 1; i++) {
		bytes[j] = *(buffer + i);
		j++;
	}
	// printf("\n");
}


u4 Cp_info::getConstantPoolTag(u2 tag, u4 utf8_size) {
	int32_t size = 0;

	// printf("tag: %d\n", tag);
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
			size = sizeof(CONSTANT_Double_info) - 2; 
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
	// printf("%d\n", size - 1);
	if (size <= 0) {
		return size;
	}
	else {
		return size - 1;
	}
}

void Cp_info::addElement(u2 tag, u4 size, u4 position, u4 currentSize, unsigned char* byte_array) {
	uint8_t buffer[size];
	struct cp_info element;

	for (uint32_t i = 0; i < size; i++) {
		int8_t val;
		val = *(byte_array + currentSize + position);
		buffer[i] = val;
		position++;
	}

	// printf("%d\n", typeid(buffer[0]));
	// printf("%d\n", buffer[0]);
	element.tag = buffer[0];
	switch (tag) {
		case CONSTANT_Class: {
			CONSTANT_Class_info *class_info = new CONSTANT_Class_info();
			class_info->tag = buffer[0];
			class_info->name_index = (buffer[1] << 16) + (buffer[2] << 8);
			element.constant_element.c1 = class_info;
			break;
		}
		case CONSTANT_Methodref: {
			CONSTANT_Methodref_info *methodref_info = new CONSTANT_Methodref_info();
			methodref_info->tag = buffer[0];
			methodref_info->class_index = (buffer[1] << 16) + (buffer[2] << 8);
			methodref_info->name_and_type_index = (buffer[3] << 16) + (buffer[4] << 8);
			element.constant_element.c2 = methodref_info;
			// printf("tag: %x\n", methodref_info->tag);
			// printf("class_index: %x\n", methodref_info->class_index);
			// printf("name: %x\n", methodref_info->name_and_type_index);
			break;
		}
		case CONSTANT_Fieldref: {
			CONSTANT_Fieldref_info *fieldref_info = new CONSTANT_Fieldref_info();
			fieldref_info->tag = buffer[0];
			fieldref_info->class_index = (buffer[1] << 16) + (buffer[2] << 8);
			fieldref_info->name_and_type_index = (buffer[3] << 16) + (buffer[4] << 8);
			element.constant_element.c3 = fieldref_info;
			// printf("tag: %x\n", fieldref_info->tag);
			// printf("class_index: %x\n", fieldref_info->class_index);
			// printf("name: %x\n", fieldref_info->name_and_type_index);
			break;
		}
		case CONSTANT_InterfaceMethodref: {
			CONSTANT_InterfaceMethodref_info *interfacemethodref_info= new CONSTANT_InterfaceMethodref_info();
			interfacemethodref_info->tag = buffer[0];
			interfacemethodref_info->class_index = (buffer[1] << 16) + (buffer[2] << 8);
			interfacemethodref_info->name_and_type_index = (buffer[3] << 16) + (buffer[4] << 8);
			element.constant_element.c4 = interfacemethodref_info;
			// printf("tag: %x\n", interfacemethodref_info->tag);
			// printf("class_index: %x\n", interfacemethodref_info->class_index);
			// printf("name: %x\n", interfacemethodref_info->name_and_type_index);
			break;
		}
		case CONSTANT_String: {
			CONSTANT_String_info *string_info = new CONSTANT_String_info();
			string_info->tag = buffer[0];
			string_info->string_index = (buffer[1] << 16) + (buffer[2] << 8);
			element.constant_element.c5 = string_info;
			break;
		}
		case CONSTANT_Integer: {
			CONSTANT_Integer_info *integer_info = new CONSTANT_Integer_info();
			integer_info->tag = buffer[0];
			integer_info->bytes = (buffer[1] << 24) + (buffer[2] << 16) + (buffer[3] << 8) + (buffer[4]); 
			element.constant_element.c6 = integer_info;
			break;
		}
		case CONSTANT_Float: {
			CONSTANT_Float_info *float_info = new CONSTANT_Float_info();
			float_info->tag = buffer[0];
			float_info->bytes = (buffer[1] << 24) + (buffer[2] << 16) + (buffer[3] << 8) + (buffer[4]); 
			element.constant_element.c7 = float_info;
			break;
		}
		case CONSTANT_Long: {
			CONSTANT_Long_info *long_info = new CONSTANT_Long_info();
			long_info->tag = buffer[0];
			long_info->high_bytes = (buffer[1] << 24) + (buffer[2] << 16) + (buffer[3] << 8) + (buffer[4]);
			long_info->low_bytes = (buffer[5] << 24) + (buffer[6] << 16) + (buffer[7] << 8) + (buffer[8]);
			element.constant_element.c8 = long_info;
			break;
		}
		case CONSTANT_Double: {
			CONSTANT_Double_info *double_info = new CONSTANT_Double_info();
			double_info->tag = buffer[0];
			double_info->high_bytes = (buffer[1] << 24) + (buffer[2] << 16) + (buffer[3] << 8) + (buffer[4]);
			double_info->low_bytes = (buffer[5] << 24) + (buffer[6] << 16) + (buffer[7] << 8) + (buffer[8]);
			// printf("tag: %d\n", double_info->tag);
			// printf("high_bytes: %x\n", double_info->high_bytes);
			// printf("low_bytes: %x\n", double_info->low_bytes);

			element.constant_element.c9 = double_info;
			break;
		}
		case CONSTANT_NameAndType: {
			CONSTANT_NameAndType_info *nameandtype_info = new CONSTANT_NameAndType_info();
			nameandtype_info->tag = buffer[0];
			nameandtype_info->name_index = (buffer[1] << 16) + (buffer[2] << 8);
			nameandtype_info->descriptor_index = (buffer[3] << 16) + (buffer[4] << 8);
			element.constant_element.c10 = nameandtype_info;
			break;
			// printf("tag: %d\n", nameandtype_info->tag);
			// printf("index: %x\n", nameandtype_info->name_index);
			// printf("descriptor_index: %x\n", nameandtype_info->descriptor_index);
		}
		case CONSTANT_Utf8: {
			int16_t utf8_size = buffer[2] + buffer[1];
			CONSTANT_Utf8_info *utf8_info = new CONSTANT_Utf8_info();	
			utf8_info->tag = buffer[0];
			utf8_info->length = utf8_size;
			utf8_info->bytes = new uint8_t[utf8_size];
			concatBytes(buffer, utf8_info->length + 2, utf8_info->bytes);
			element.constant_element.c11 = utf8_info;
			break;
		}
		case CONSTANT_MethodHandle: {
			CONSTANT_MethodHandle_info *methodhandle_info = new CONSTANT_MethodHandle_info();
			methodhandle_info->tag = buffer[0];
			methodhandle_info->reference_kind = buffer[1];
			methodhandle_info->reference_index = (buffer[2] << 16) + (buffer[3] << 8);
			element.constant_element.c12 = methodhandle_info;
			break;
		}
		case CONSTANT_MethodType: {
			CONSTANT_MethodType_info *methodtype_info = new CONSTANT_MethodType_info();
			methodtype_info->tag = buffer[0];
			methodtype_info->descriptor_index = (buffer[2] << 16) + (buffer[3] << 8);
			element.constant_element.c13 = methodtype_info;
			break;
		}
		case CONSTANT_InvokeDynamic: {
			CONSTANT_InvokeDynamic_info *invokedynamic_info = new CONSTANT_InvokeDynamic_info();
			invokedynamic_info->tag = buffer[0];
			invokedynamic_info->bootstrap_method_attr_index = (buffer[1] << 16) + (buffer[2] << 8);
			invokedynamic_info->name_and_type_index = (buffer[3] << 16) + (buffer[4] << 8);
			element.constant_element.c14 = invokedynamic_info;
			break;
		}
	}
	this->constant_pool.push_back(element);
}

void Cp_info::getConstantPool() {
	// return this->constant_pool;
	vector<cp_info>::iterator i;
	for (i = this->constant_pool.begin(); i != this->constant_pool.end(); ++i) {
		// printf("%d\n", i->print());
		switch (i->tag) {
			case CONSTANT_Class:
				i->constant_element.c1->print();
				break;
			case CONSTANT_Fieldref:
				i->constant_element.c2->print();
				break;
			case CONSTANT_Methodref:
				i->constant_element.c3->print();
				break;
			case CONSTANT_InterfaceMethodref:
				i->constant_element.c4->print();
				break;
			case CONSTANT_String:
				i->constant_element.c5->print();
				break;
			case CONSTANT_Integer:
				i->constant_element.c6->print();
				break;
			case CONSTANT_Float:
				i->constant_element.c7->print();
				break;
			case CONSTANT_Long:
				i->constant_element.c8->print();
				break;
			case CONSTANT_Double:
				i->constant_element.c9->print();
				break;
			case CONSTANT_NameAndType:
				i->constant_element.c10->print();
				break;
			case CONSTANT_Utf8:
				i->constant_element.c11->print();
				break;
			case CONSTANT_MethodHandle:
				i->constant_element.c12->print();
				break;
			case CONSTANT_MethodType:
				i->constant_element.c13->print();
				break;
			case CONSTANT_InvokeDynamic:
				i->constant_element.c14->print();
				break;
			default:
				break;
		}
	}
}

void CONSTANT_Class_info::print()				{ printf("\tTag: Class || Name index: %x\n", name_index); }
void CONSTANT_Methodref_info::print()			{ printf("\tTag: Methodref || Class index: %d || Name and type index: %d\n", class_index, name_and_type_index); }
void CONSTANT_Fieldref_info::print()			{ printf("\tTag: Fieldref || Class index: %d || Name and type index: %d\n", class_index, name_and_type_index); }
void CONSTANT_InterfaceMethodref_info::print()	{ printf("\tTag: InterfaceMethodref || Class index: %d || Name and type index: %d\n", class_index, name_and_type_index); }
void CONSTANT_String_info::print()				{ printf("\tTag: String || String index: %d\n", string_index); }
void CONSTANT_Integer_info::print()				{ printf("\tTag: Integer || Bytes: %d\n", bytes); }
void CONSTANT_Float_info::print()				{ printf("\tTag: Float || Bytes: %d\n", bytes); }
void CONSTANT_Long_info::print()				{ printf("\tTag: Long || High bytes: 0x%x || Low bytes: 0x%x\n", high_bytes, low_bytes); }
void CONSTANT_Double_info::print()				{ printf("\tTag: Double || High bytes: 0x%x || Low bytes: 0x%x\n", high_bytes, low_bytes); }
void CONSTANT_NameAndType_info::print()			{ printf("\tTag: NameAndType || Name index: %x || Descriptor index: %x\n", name_index, descriptor_index); }
void CONSTANT_Utf8_info::print()				{ printf("\tTag: Utf8 || Length: %d || Bytes[]: %x\n", length, bytes[0]); }
void CONSTANT_MethodHandle_info::print()		{ printf("\tTag: MethodHandle || Reference kind: %d || Reference index: %d\n", reference_kind, reference_index); }
void CONSTANT_MethodType_info::print()			{ printf("\tTag: MethodType || Descriptor index: %d\n", descriptor_index); }
void CONSTANT_InvokeDynamic_info::print()		{ printf("\tTag: InvokeDynamic || Bootstrap Method Attributes Index: %d || Name and type index: %d\n", bootstrap_method_attr_index, name_and_type_index); }