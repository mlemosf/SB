#include "../include/attribute_info.hpp"
#include <string.h>
using namespace std;
Cp_info * CP_global;
u1 read1byteAtrr(u1 * byteArray){return *byteArray;}

u2 read2bytesAtrr(u1 * byteArray){
	u2 ret;
	u1 byte[2];
	byte[1] = read1byteAtrr(byteArray);
	byte[0] = read1byteAtrr(byteArray+1);
	memcpy(&ret,&byte,sizeof(u2));
	return ret;
}
u4 read4bytesAtrr(u1 * byteArray){
	u4 ret;
	u1 byte[4];
	byte[3] = read1byteAtrr(byteArray);
	byte[2] = read1byteAtrr(byteArray+1);
	byte[1] = read1byteAtrr(byteArray+2);
	byte[0] = read1byteAtrr(byteArray+3);
	memcpy(&ret,&byte,sizeof(u4));
	return ret; 
}
bool Attribute_info::setCP(Cp_info * Cp){
	this->ConstantPool = Cp;
	return true;
}
bool Attribute_info::setAttributeNameIndex(u2 attribute_name_index){
	this->attribute_name_index = attribute_name_index;
	return true;
}

bool Attribute_info::setAttributeLength(u4 attribute_length){
	this->attribute_length = attribute_length;
	return true;
}

u4 Attribute_info::setInfo(char * typeAttribute,uint8_t sizeTypeAtrr, u1 * infoAttr){
	string attributeName;
	unsigned int i;
	for(i =0;i<sizeTypeAtrr;i++)attributeName.push_back(typeAttribute[i]);

	if(attributeName== "Code"){
		this->info.codeAttr->setCP(this->ConstantPool);// setando o CP no CodeAttribute
		this->info.codeAttr = new Code_attribute();
		i = 0;
		while(i < this->attribute_length){
			this->info.codeAttr->setMax_stack(read2bytesAtrr(infoAttr+i));
			i+=2;
			this->info.codeAttr->setMax_locals(read2bytesAtrr(infoAttr+i));
			i+=2;
			this->info.codeAttr->setCode_length(read4bytesAtrr(infoAttr+i));
			i+=4;
			this->info.codeAttr->setCode(infoAttr+i); // Code atribute se vira
			i+=this->info.codeAttr->getCode_length();
			this->info.codeAttr->setExceptionTableLength(read2bytesAtrr(infoAttr+i));
			i+=2;
			this->info.codeAttr->setException_table(infoAttr+i); // Code atribute se vira
			i+=(this->info.codeAttr->getExceptionTableLength()*8);
			this->info.codeAttr->setAttributeCount(read2bytesAtrr(infoAttr+i));
			i+=2;
			i += this->info.codeAttr->setAttributes(infoAttr+i); // Code atribute se vira
			
		}
	}else if(attributeName == "Deprecated"){
		this->info.deprecatedAttr = new Deprecated_attribute();
		
	}else if(attributeName == "Exceptions"){
		this->info.exceptionAttr = new Exceptions_attribute();

	}else if(attributeName ==  "InnerClasses"){
		this->info.innerClassesAttr = new InnerClasses_attribute();

	}else if(attributeName == "SourceFile"){
		this->info.sourceFileAttr = new SourceFile_attribute();

	}else if(attributeName == "Synthetic"){
		this->info.syntheticAttr = new Synthetic_attribute();

	}else if(attributeName == "LineNumberTable"){
		this->info.LineNumberTableAtrr = new LineNumberTable_attribute();

	}else if(attributeName == "LocalVariableTable"){
		this->info.LocalVariableTableAttr = new LocalVariableTable_attribute();
	}
	return i;
}
u2 Attribute_info::getAttributeNameIndex(){
	return this->attribute_name_index;
}

u4 Attribute_info::getAttributeLength(){
	return this->attribute_length;
}

void Attribute_info::print(){
	printf("Attribute name index: %d\n",attribute_name_index);
	printf("Attribute length: %d\n",attribute_length);
	printf("Specific Info:\n"); // colocar a lista de atributos
}

// Code Attribute
bool Code_attribute::setCP(Cp_info * Cp){
	this->ConstantPool = Cp;
	return true;
}
bool Code_attribute::setMax_stack(u2  Maxstack){
	this->max_stack = Maxstack;
	return true;
}

u2 Code_attribute::getMax_stack(){
	return this->max_stack;
}

bool Code_attribute::setMax_locals(u2 MaxLocals){
	this->max_locals=MaxLocals;
	return true;
}

u2 Code_attribute::getMax_locals(){
	return this->max_locals;
}

bool Code_attribute::setCode_length(u4 CodeLength){
	this->code_length = CodeLength;
	return true;
}

u4 Code_attribute::getCode_length(){
	return this->code_length;
}

bool Code_attribute::setCode(u1 * Code){
	this->code = (u1 *)malloc(this->code_length);
	for(unsigned int i=0;i<this->code_length;i++){
		this->code[i] = Code[i];
	}
	return true;
}

u1 * Code_attribute::getCode(){
	return this->code;
}

bool Code_attribute::setExceptionTableLength(u2 ExceptTableLength){
	this->exception_table_length = ExceptTableLength;
	return true;
}

u2 Code_attribute::getExceptionTableLength(){
	return this->exception_table_length;
}

bool Code_attribute::setException_table(u1 * ExceptTable){
	//ExceptionCode_info * ExceptionTable; variavel nao utilizada
	int i=0;
	while(i<(8 * this->exception_table_length)){
		this->exception_table[i].start_pc = read2bytesAtrr(ExceptTable+i);
		i+=2;
		this->exception_table[i].end_pc = read2bytesAtrr(ExceptTable+i);
		i+=2;
		this->exception_table[i].handler_pc =read2bytesAtrr(ExceptTable+i);
		i+=2;
		this->exception_table[i].catch_type = read2bytesAtrr(ExceptTable+i);
		i+=2;
	}
	return true;
}
ExceptionCode_info * Code_attribute::getExceptionTable(){
	return this->exception_table;
}

bool Code_attribute::setAttributeCount(u2 AttrCount){
	this->attributes_count = AttrCount;
	return true;
}
u2  Code_attribute::getAttributesCount(){
	return this->attributes_count;
}
u4 Code_attribute::setAttributes(u1 * Attrs){
	Attribute_info * attributes = (Attribute_info *)malloc(sizeof(Attribute_info));
	cp_info Cp_infoAux;
	char nameIndexAttribute[50];
	u2 lengthNameIndex;
	//this->attributes = (Attribute_info *)malloc(this->attributes_count*sizeof(Attribute_info));
	int i =0,j=0;
	while(j<this->attributes_count){
		attributes->setAttributeNameIndex(read2bytesAtrr(Attrs+i));
		i+=2;
		attributes->setAttributeLength(read4bytesAtrr(Attrs+i));
		i+=4;
		Cp_infoAux = this->ConstantPool->getCpInfoElement(attributes->getAttributeNameIndex()); // pegando o nome do attrbute
		lengthNameIndex = Cp_infoAux.constant_element.c11->length;
		strcpy(nameIndexAttribute,(const char *)Cp_infoAux.constant_element.c11->bytes);
		nameIndexAttribute[lengthNameIndex]= '\0';
		i += attributes->setInfo(nameIndexAttribute,lengthNameIndex,Attrs+i);
		j++;
	}
	return i;
}