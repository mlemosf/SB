#include "../include/method_info.hpp"
using namespace std;

bool Method_info::setAccessFlags(u2 access_flags){
	this->access_flags = access_flags;
	return true;
}

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

bool Method_info::setAttributes(){
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
	switch(acess_flags){
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
 		  printf("[synchronized]")
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
}