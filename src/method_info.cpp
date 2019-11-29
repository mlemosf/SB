#include "../include/method_info.hpp"
#include "../include/cp_info.hpp"
#include "../include/leitor.hpp"
using namespace std;

bool Method_info::setFields(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count, Attribute_info* attributes) {
	method_info_element *element = (method_info_element*)malloc(sizeof(method_info_element));
	element->access_flags = access_flags;
	element->name_index = name_index;
	element->descriptor_index = descriptor_index;
	element->attributes_count = attributes_count;
	element->attributes = attributes;
	methods.push_back(element);
	return true;
}

method_info_element* Method_info::getMethod(u2 index) {
	return this->methods[index];
}

void Method_info::getMethodInfo() {
	vector<method_info_element*>::iterator i;
	int j = 0;
	for (i = this->methods.begin(); i != this->methods.end(); ++i) {
		printf("========== [%d] ===========\n", j);
		printf("Access_flags: 0x000%x\n", (*i)->access_flags);
		printf("Name index: %d\n", (*i)->name_index);
		printf("Descriptor index: %d\n", (*i)->descriptor_index);
		printf("Attribute count: %d\n", (*i)->attributes_count);
		printf("Attributes: \n");
		info_element* element = (*i)->attributes->getInfoElement();
		for (int j = 0; j < (*i)->attributes_count; j++) {
			printf("  Attribute name index: %d\n", element->codeAttr->attribute_name_index);
			printf("  Attribute length: %d\n", element->codeAttr->attribute_length);
			printf("  Minor version: %d\n", element->codeAttr->minor_version);
			printf("  Maximum local variables: %d\n", element->codeAttr->max_locals);
			printf("  Code length: %d\n", element->codeAttr->code_length);
			printf("  Bytecode: ");
			u1* bytecode = element->codeAttr->code;
			for (int k = 0; k < element->codeAttr->code_length; k++) {
				printf("%x ", *(bytecode + k));
			}
			printf("\n");
			printf("  Line number table:\n");
			Attribute_info* line_number_table = element->codeAttr->attributes;
			printf("\tAttribute name index: %d\n", line_number_table->getAttributeNameIndex());
			printf("\tAttribute length: %d\n", line_number_table->getAttributeLength());
			printf("\tSpecific info: ");
			u1 *info = line_number_table->getInfo();
			for (int l = 0; l < line_number_table->getAttributeLength(); l++) {
				printf("%x ", *(info + l));
			}
			printf("\n");


		}
		printf("=====================\n");
		j++;
	}
}

// bool Method_info::setAccessFlags(u2 access_flags){
// 	this->access_flags = access_flags;
// 	return true;
// }
/*
bool Method_info::setNameIndex(u2 name_index){
	this->name_index = name_index;
	return true;
}

bool Method_info::setDescriptorIndex(u2 descriptor_index){
	this->descriptor_index = descriptor_index;
	return true;
}

bool Method_info::setAttributeCount(u2 attributes_count){
	this->attributes_count = attributes_count;
	return true;
}

bool Method_info::setAttributes(Cp_info constant_pool){
	for (u2 i = 0; i < this->attributes_count; ++i){		
		u2 attribute_name_index = read2byte();
		u4 attribute_length = read4byte();

		switch(this->constant_pool[attribute_name_index]){
			case "Code":
				Code_attribute code_aux;
				code_aux.attribute_name_index = attribute_name_index;
				code_aux.attribute_length = attribute_length;
				code_aux.max_stack = read2byte();
				code_aux.max_locals = read2byte();
				code_aux.code_length = read4byte();

				for (u2 k = 0; k < code_aux.code_length; ++k){
					code_aux.code[k] = read1byte();
				}

				code_aux.exception_table_length = read2byte();

				for (int k = 0; k < code_aux.exception_table_length; ++k){
					ExceptionCode_info b;
					b.start_pc = read2byte();
					b.end_pc = read2byte();
					b.handler_pc = read2byte();
					b.catch_type = read2byte();

					code_aux.exception_table[k] = b;
				}

				code_aux.attributes_count = read2byte();

				code_aux.setAttributes();
				this->attributes[i] = cv_aux;
				break;
			case "Exceptions":
				j = 3;
				Exceptions_attribute exc_aux;
				exc_aux.attribute_name_index = attribute_name_index;
				exc_aux.attribute_length = attribute_length;

				exc_aux.number_of_exceptions = read2byte();

				for (int k = 0; k < exc_aux.number_of_exceptions; ++k){
					exc_aux.exception_index_table[k] = read2byte();
				}

				this->attributes[i] = exc_aux;
				break;
			case "Synthetic":
				Synthetic_attribute syn_aux;
				syn_aux.attribute_name_index = attribute_name_index;
				syn_aux.attribute_length = attribute_length;

				this->attributes[i] = syn_aux;
				break;
			case "Deprecated":
				Deprecated_attribute dep_aux;
				dep_aux.attribute_name_index = attribute_name_index;
				dep_aux.attribute_length = attribute_length;

				this->attributes[i] = dep_aux;
				break;
		}

	}

	this->attributes[i] = attributes[i];
	
	return true;
}

u2 Method_info::getAccessFlags(){
	return this->access_flags = access_flags;
}

u2 Method_info::getNameIndex(){
	return this->name_index;
}

u2 Method_info::getDescriptorIndex(){
	return this->descriptor_index;
}

u2 Method_info::getAttributeCount(){
	return this->attributes_count;
}

Attribute_info* Method_info::getAttributes(){
	return this->attributes;
}

void Method_info::print(){
	printf("Name Index: %d\n",name_index);
	printf("Descriptor Index: %d\n",descriptor_index);
	printf("Acess Flags: %x",access_flags);
	switch(access_flags){
		case ACC_PUBLIC:
		  printf("[public]");
		  break;
    case ACC_PRIVATE:
      printf("[private]");
      break;
		case ACC_PROTECTED:
		  printf("[protected]");
		  break;
		case ACC_STATIC:
		  printf("[static]");
		  break;
		case ACC_FINAL:
		  printf("[final]");
		  break;
		case ACC_SYNCHRONIZED: 
 		  printf("[synchronized]");
 		  break;
 		case ACC_BRIDGE:
 		  printf("[bridge]");
 		  break;
 		case ACC_VARARGS:
 		  printf("[varargs]");
 		  break; 
 		case ACC_NATIVE:
 		  printf("[native]");
 		  break; 
 		case ACC_ABSTRACT:
 		  printf("[abstract]");
 		  break; 
 		case ACC_STRICT:
 		  printf("[strict]");
 		  break; 
		case ACC_SYNTHETIC:
		  printf("[synthetic]");
		  break;
	}
	printf("\n");
}*/