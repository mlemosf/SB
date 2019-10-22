#include "../include/attribute_info.hpp"
using namespace std;

bool Attribute_info::setAttributeNameIndex(u2 attribute_name_index){
	this->attribute_name_index = attribute_name_index;
	return true;
}

Attribute_info::setAttributeLenght(u4 attribute_lenght){
	this->attribute_lenght = attribute_lenght;
	return true;
}

Attribute_info::setInfo(u1* info){
	for (int i = 0; i < this->attribute_lenght; ++i){
		this->info[i] = info[i];
	}
	return true;
}

u2 Attribute_info::getAttributeNameIndex(){
	return this->attribute_name_index;
}

u2 Attribute_info::getAttributeLenght(){
	return this->attribute_lenght;
}

u1* Attribute_info::getInfo(){
	return this->info;
}