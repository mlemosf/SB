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

bool Method_info::setAttributes(Attribute_info * attributes){
	for (int i = 0; i < this->attributes_count; ++i){
		this->attributes[i] = attributes[i];
	}
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