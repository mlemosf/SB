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

bool Code_attribute::setAttributes(unsigned char* byte_array, u4 current_size){
	return true;
}

void Attribute_info::print(){
	printf("Attribute name index: %d\n",attribute_name_index);
	printf("Attribute length: %d\n",attribute_length);
	printf("Specific Info:\n"); // colocar a lista de atributos
}