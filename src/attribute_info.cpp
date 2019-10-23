#include "../include/attribute_info.hpp"
using namespace std;

bool Attribute_info::setAttributeNameIndex(u2 attribute_name_index){
	this->attribute_name_index = attribute_name_index;
	return true;
}

bool Attribute_info::setAttributeLength(u4 attribute_length){
	this->attribute_length = attribute_length;
	return true;
}

bool Attribute_info::setInfo(u1* info){
	for (u4 i = 0; i < this->attribute_length; ++i){
		this->info[i] = info[i];
	}
	return true;
}

u2 Attribute_info::getAttributeNameIndex(){
	return this->attribute_name_index;
}

u4 Attribute_info::getAttributeLength(){
	return this->attribute_length;
}

u1* Attribute_info::getInfo(){
	return this->info;
}

bool Code_attribute::setAttributes(Cp_info constant_pool){
	for (u2 i = 0; i < this->attributes_count; ++i){
			
		u2 attribute_name_index = read2byte();
		u4 attribute_length = read4byte();

		switch(this->constant_pool[attribute_name_index]){
			case "LineNumberTable":
				LineNumberTable_attribute lnt_aux;
				lnt_aux.attribute_name_index = attribute_name_index;
				lnt_aux.attribute_length = attribute_length;

				lnt_aux.line_number_table_length = read2byte();

				for (u2 k = 0; k < lnt_aux.line_number_table_length; ++k){
					LineNumber_info d;

					d.start_pc = read2byte();
					d.line_number = read2byte();

					lnt_aux.line_number_table[k] = d;
				}

				this->attributes[i] = lnt_aux;

				break;
			case "LocalVariableTable":
				LocalVariableTable_attribute local_aux;
				local_aux.attribute_name_index = attribute_name_index;
				local_aux.attribute_length = attribute_length;

				local_aux.local_variable_table_length = read2byte();

				for (int k = 0; k < local_aux.local_variable_table_length; ++k){
					LocalVariableTable_info e;

					e.start_pc = read2byte();
					e.length = read2byte();
					e.name_index = read2byte();
					e.descriptor_index = read2byte();
					e.index = read2byte();

					local_aux.local_variable_table[k] = e;
				}
				this->attributes[i] = local_aux;

				break;
		}

	}

	return true;
}

void Attribute_info::print(){
	printf("Attribute name index: %d\n",attribute_name_index);
	printf("Attribute length: %d\n",attribute_length);
	printf("Specific Info:\n"); // colocar a lista de atributos
}