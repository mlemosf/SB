#include "../include/leitor.hpp"
#include "../include/field_info.hpp"
#include "../include/attribute_info.hpp"
using namespace std;

u1 Leitor::read1byte(){
	u1 ret;
	ret = *(this->byte_array + this->current_size);
	this->current_size += sizeof(ret);
	return ret;
}

u2 Leitor::read2byte(){
	u2 b[1];
	u1 ret[2];
	ret[1] = read1byte();
	ret[0] = read1byte();
	memcpy(b, &ret, sizeof(u2));
	return *b;
}

u4 Leitor::read4byte(){
	u4 b[1];
	u1 ret[4];
	ret[3] = read1byte();
	ret[2] = read1byte();
	ret[1] = read1byte();
	ret[0] = read1byte();
	memcpy(b, &ret, sizeof(u4));
	return *b;
}


/* LEITOR */

void Leitor::loadFile(const string filename) {
	ifstream classfile;
	classfile.open(filename, ios::in|ios::binary);

	classfile.seekg(0, ios::end);
	int32_t filesize = classfile.tellg();

	char buffer;
	unsigned char *fileContent = new unsigned char[filesize];
	classfile.seekg(0, ios::beg);
	
	if (classfile.is_open()) {
		int32_t i = 0;
		while(!classfile.eof()) {
			classfile.read(&buffer, 1);
			fileContent[i] = static_cast<unsigned char>(buffer);
			i++;
		}
	}
	else {
		printf("Unable to open file\n");
	};
	this->byte_array = fileContent;
}

bool Leitor::setMagicNumber() {
	int32_t size = 4;
	int32_t buffer[size];
	unsigned char magic[size];
	int32_t j = size - 1;
	bool result  = false;

	for (int32_t i = 0; i < size; i++) {
		magic[j]= *(this->byte_array + i);
		j--;
	}

	memcpy(buffer, &magic, sizeof(magic));

	if (*buffer == (int32_t)0xcafebabe)  {
		this->magic = *buffer;
		result = true;
	}
	else {
		printf("Invalid class file\n");
	}
	this->current_size = sizeof(this->magic);
	return result;
}

u4 Leitor::getMagicNumber(){return this->magic;}

bool Leitor::setMinorVersion() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t minor_version[size];

	for (int32_t i = 0; i < size; i++) {
		minor_version[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &minor_version, sizeof(minor_version));
	this->minor_version = *buffer;
	this->current_size += sizeof(this->minor_version);
	return true;
}

u2 Leitor::getMinorVersion(){return this->minor_version;}

bool Leitor::setMajorVersion() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t major_version[size];

	for (int32_t i = 0; i < size; i++) {
		major_version[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &major_version, sizeof(major_version));
	this->major_version = *buffer;
	this->current_size += sizeof(this->major_version);
	return true;
}

u2 Leitor::getMajorVersion(){return this->major_version;}

bool Leitor::setConstantPoolCount() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t constant_pool_count[size];

	for (int32_t i = 0; i < size; i++) {
		constant_pool_count[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &constant_pool_count, sizeof(constant_pool_count));
	this->constant_pool_count = *buffer;
	this->current_size += sizeof(this->constant_pool_count);
	return true;
}

u2 Leitor::getConstantPoolCount(){return this->constant_pool_count;}

bool Leitor::setConstantPool() {

	int32_t size = this->constant_pool_count - 2;
	int8_t tag;
	int32_t ret = 0;
	int32_t pos = 0;
	int32_t utf8_size = 0;

	Cp_info *constant_pool = new Cp_info();

	for (int32_t i = 0; i < this->constant_pool_count; i++) {
		tag = *(this->byte_array + this->current_size + pos);
		utf8_size = *(this->byte_array + this->current_size + pos + 2);
		ret = constant_pool->getConstantPoolTag(tag, utf8_size);
		pos += ret;
		printf("tag: %d\n", tag);
	}
	delete(constant_pool);

	this->current_size += size;
	return true;
}

u2 Leitor::getInterfacesCount(){return interfaces_count;}

bool Leitor::setAccessFlags() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t access_flags[size];

	for (int32_t i = 0; i < size; i++) {
		access_flags[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &access_flags, sizeof(access_flags));
	this->access_flags = *buffer;
	this->current_size += sizeof(this->access_flags);
	return true;
}

u2 Leitor::getFieldsCount(){return fields_count;}

bool Leitor::setThisClass() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t this_class[size];

	for (int32_t i = 0; i < size; i++) {
		this_class[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &this_class, sizeof(this_class));
	this->this_class = *buffer;
	this->current_size += sizeof(this->this_class);
	return true;
}

u2 Leitor::getMethodsCount(){return methods_count;}

bool Leitor::setSuperClass() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t super_class[size];

	for (int32_t i = 0; i < size; i++) {
		super_class[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &super_class, sizeof(super_class));
	this->super_class = *buffer;
	this->current_size += sizeof(this->super_class);
	return true;
}

u2 Leitor::getAttributesCount(){return attributes_count;}

bool Leitor::setInterfacesCount() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t interfaces_count[size];

	for (int32_t i = 0; i < size; i++) {
		interfaces_count[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &interfaces_count, sizeof(interfaces_count));
	this->interfaces_count = *buffer;
	this->current_size += sizeof(this->interfaces_count);
	return true;
}

/*

bool Leitor::setInterfaces(){
	int32_t size = this->attributes_count;
	uint16_t interfaces[size];
	uint16_t buffer[size];
	int16_t j = size-1;
	for(int32_t i=0;i<size;i++){
		interfaces[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer,&interfaces,sizeof(interfaces));
	this->interfaces = buffer;
	this->current_size +=  sizeof(interfaces);

	return true;
}
*/

bool Leitor::setFieldsCount() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t fields_count[size];

	for (int32_t i = 0; i < size; i++) {
		fields_count[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &fields_count, sizeof(fields_count));
	this->fields_count = *buffer;
	this->current_size += sizeof(this->fields_count);
	return true;
}
/*
bool Leitor::setFields(){
	uint16_t size = this->fields_count;
	int32_t j = size - 1;
	Field_info fields[size];
	int32_t sizeU2 =  2;
	int32_t j_aux = sizeU2-1;
	int16_t * buffer;
	uint8_t access_flags[sizeU2];
	uint8_t name_index[sizeU2]; 
	uint8_t descriptor_index[sizeU2];
	uint8_t attributes_count[sizeU2];
	Attribute_info * attributes;
	for(int32_t i =0;i<size;i++){
		for(int32_t k=0;k<sizeU2;k++){
			access_flags[j_aux] = *(this->byte_array + this->current_size+ k);
			j_aux--;
		}
		memcpy(buffer,&access_flags,sizeof(buffer));
		fields[i].setAcessFlags(*buffer);
		j_aux = sizeU2-1;
		for(int32_t k=0;k<sizeU2;k++){
			name_index[j_aux] = *(this->byte_array + this->current_size+ k);
			j_aux--;
		}
		memcpy(buffer,&name_index,sizeof(buffer));
		fields[i].setNameIndex(*buffer);
		j_aux = sizeU2-1;
		for(int32_t k=0;k<sizeU2;k++){
			descriptor_index[j_aux] = *(this->byte_array + this->current_size+ k);
			j_aux--;
		}
		memcpy(buffer,&descriptor_index,sizeof(buffer));
		fields[i].setDescriptorIndex(*buffer);
		j_aux=sizeU2-1;
		for(int32_t k=0;k<sizeU2;k++){
			attributes_count[j_aux] =  *(this->byte_array + this->current_size+ k);
			j_aux--;
		}
		memcpy(buffer,&attributes_count,sizeof(buffer));
		fields[i].setAttributesCount(*buffer);
		//for(int32_t k=0;k < this->attributes_count;k++){	
		//}
	}
	return true;
}
*/
bool Leitor::setMethodsCount() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t methods_count[size];

	for (int32_t i = 0; i < size; i++) {
		methods_count[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &methods_count, sizeof(methods_count));
	this->methods_count = *buffer;
	this->current_size += sizeof(this->methods_count);
	return true;
}

bool Leitor::setMethods(){

	printf("methods_count: %d\n", this->methods_count);
	int32_t size = 2;
	int32_t j = size-1;
	//int32_t cont = 0;
	int16_t access_flags[size];
	int16_t name_index[size];
	int16_t descriptor_index[size];
	int16_t attributes_count[size];

	Method_info a[this->methods_count];
	for (int i = 0; i < this->methods_count; ++i){
		for (int k = 0; k < size; ++k){
			access_flags[j] = *(this->byte_array + this->current_size + k);
			j--;
		}
		//printf("access_flags: 0x%04x\n", *access_flags);
		this->current_size += sizeof(u2);
		a[i].setAccessFlags(*access_flags);
		j = size-1;
		for (int k = 0; k < size; ++k){
			name_index[j] = *(this->byte_array + this->current_size + k);
			j--;
		}
		a[i].setNameIndex(*name_index);
		this->current_size += sizeof(u2);
		j = size-1;
		for (int k = 0; k < size; ++k){
			descriptor_index[j] = *(this->byte_array + this->current_size + k);
			j--;
		}
		a[i].setDescriptorIndex(*descriptor_index);
		this->current_size += sizeof(u2);
		j = size-1;
		for (int k = 0; k < size; ++k){
			attributes_count[j] = *(this->byte_array + this->current_size + k);
			j--;
		}
		this->current_size += sizeof(u2);
		a[i].setAttributeCount(*attributes_count);
		j = size-1;
		/*a[i].setAttributes(this->attributes+cont);
		cont+=a[i].getAttributeCount();*/
	}
	this->methods = a;
	this->current_size+=sizeof(a)*this->methods_count;
	return true;
}

bool Leitor::setAttributesCount() {
	int32_t size = 2;
	int32_t j = size - 1;
	int16_t buffer[size];
	int16_t attributes_count[size];

	for (int32_t i = 0; i < size; i++) {
		attributes_count[j] = *(this->byte_array + this->current_size + i);
		j--;
	}
	memcpy(buffer, &attributes_count, sizeof(attributes_count));
	this->attributes_count = *buffer;
	this->current_size += sizeof(this->attributes_count);
	return true;
}

/*bool Leitor::setAttributes(){
	int32_t size = 2;
	u4 j = size-1;
	int16_t attribute_name_index[size];
	int16_t attribute_length[4];

	for (u4 i = 0; i < this->attributes_count; ++i){
		for (int32_t k = 0; k < size; ++k){
			attribute_name_index[j] = (*this->byte_array + this->current_size + k);
			j--;
		}
		this->current_size+=sizeof(u2);
		switch(this->constant_pool[*attribute_name_index]){
			case "ConstantValue":
				ConstantValue_attribute cv_aux;
				int16_t constantvalue_index[2];
				cv_aux.attribute_name_index = *attribute_name_index;
				cv_aux.attribute_length = 2;
				j = cv_aux.attribute_length-1;
				for (u4 k = 0; k < cv_aux.attribute_length; ++k){
					constantvalue_index[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				this->current_size+=sizeof(u2);
				cv_aux.constantvalue_index = *constantvalue_index;
				break;
			case "Code":
				Code_attribute code_aux;
				for (int k = 0; k < 4; ++k){
					attribute_length[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				code_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u4);
				
				int8_t max_stack[2];
				j = 1;
				for (int k = 0; k < 2; ++k){
					max_stack[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				code_aux.max_stack = *max_stack;
				this->current_size+=sizeof(u2);
				
				int8_t max_locals[2];
				j = 1;
				for (int k = 0; k < 2; ++k){
					max_locals[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				code_aux.max_locals = *max_locals;
				this->current_size+=sizeof(u2);
				
				int8_t code_length[4];
				j = 3;
				for (int k = 0; k < 4; ++k){
					code_length[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				code_aux.code_length = *code_length;
				this->current_size+=sizeof(u4);

				j = code_aux.code_length-1;
				for (u2 k = 0; k < code_aux.code_length; ++k){
					code_aux.code[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				this->current_size+=sizeof(u1)*code_aux.code_length;

				int8_t exception_table_length[2];
				j = 1;
				for (int k = 0; k < 2; ++k){
					exception_table_length[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				code_aux.exception_table_length = *exception_table_length;
				this->current_size+=sizeof(u2);

				for (int k = 0; k < code_aux.exception_table_length; ++k){
					ExceptionCode_info b;
					j = 1;
					int8_t start_pc[2];
					for (u2 l = 0; l < 2; ++l){
						start_pc[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					b.start_pc = *start_pc;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t end_pc[2];
					for (u2 l = 0; l < 2; ++l){
						end_pc[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					b.end_pc = *end_pc;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t handler_pc[2];
					for (u2 l = 0; l < 2; ++l){
						handler_pc[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					b.handler_pc = *handler_pc;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t catch_type[2];
					for (u2 l = 0; l < 2; ++l){
						catch_type[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					b.catch_type = *catch_type;
					this->current_size+=sizeof(u2);

					code_aux.exception_table[k] = b;
				}

				j = 1;
				int8_t attributes_count[2];
				for (u2 k = 0; k < 2; ++k){
					attributes_count[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				code_aux.attributes_count = *attributes_count;
				this->current_size+=sizeof(u2);

				code_aux.setAttributes(this->byte_array, this->current_size);
				break;

			case "Exceptions":
				j = 3;
				Exceptions_attribute exc_aux;
				for (u4 k = 0; k < 4; ++k){
					attribute_length[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				exc_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u4);

				j = 1;
				int8_t number_of_exceptions[2];
				for (u2 k = 0; k < 2; ++k){
					number_of_exceptions[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				exc_aux.number_of_exceptions = *number_of_exceptions;
				this->current_size+=sizeof(u2);

				for (int k = 0; k < exc_aux.number_of_exceptions; ++k){
					j = 1;
					int8_t var_exc[2];
					for (u2 l = 0; l < 2; ++l){
						var_exc[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					exc_aux.exception_index_table[k] = *var_exc;
					this->current_size+=sizeof(u2);
				}

				break;

			case "InnerClasses":
				InnerClasses_attribute in_aux;

				j = 3;
				for (u2 k = 0; k < 4; ++k){
					attribute_length[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				in_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u4);

				j = 1;
				int8_t number_of_classes[2];
				for (u2 k = 0; k < 2; ++k){
					number_of_classes[j] = (*this->byte_array + this->current_size + k);
					j--;
				}
				in_aux.number_of_classes = *number_of_classes;
				this->current_size+=sizeof(u2);

				for (int k = 0; k < in_aux.number_of_classes; ++k){
					ClassInners_info c;
					
					j = 1;
					int8_t inner_class_info_index[2];
					for (u2 l = 0; l < 2; ++l){
						inner_class_info_index[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					c.inner_class_info_index = *inner_class_info_index;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t outer_class_info_index[2];
					for (u2 l = 0; l < 2; ++l){
						outer_class_info_index[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					c.outer_class_info_index = *outer_class_info_index;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t inner_name_index[2];
					for (u2 l = 0; l < 2; ++l){
						inner_name_index[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					c.inner_name_index = *inner_name_index;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t inner_class_access_flags[2];
					for (u2 l = 0; l < 2; ++l){
						inner_class_access_flags[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					c.inner_class_access_flags = *inner_class_access_flags;
					this->current_size+=sizeof(u2);

					in_aux.classes[k] = c;	
				}

				break;

			case "Synthetic":
				Synthetic_attribute syn_aux;

				j = 3;
				for (u2 l = 0; l < 4; ++l){
					attribute_length[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				syn_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u4);

				break;

			case "SourceFile":
				SourceFile_attribute source_aux;

				j = 3;
				for (u2 l = 0; l < 4; ++l){
					attribute_length[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				source_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u4);

				j = 1;
				int8_t sourcefile_index[2];
				for (u2 l = 0; l < 2; ++l){
					sourcefile_index[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				source_aux.sourcefile_index = *sourcefile_index;
				this->current_size+=sizeof(u2);

				break;
			
			case "LineNumberTable":
				LineNumberTable_attribute lnt_aux;

				j = 3;
				for (u2 l = 0; l < 4; ++l){
					attribute_length[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				lnt_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u4);

				j = 1;
				int8_t line_number_table_length[2];
				for (u2 l = 0; l < 2; ++l){
					line_number_table_length[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				lnt_aux.line_number_table_length = *line_number_table_length;
				this->current_size+=sizeof(u2);

				for (u2 k = 0; k < lnt_aux.line_number_table_length; ++k){
					LineNumber_info d;

					j = 1;
					int8_t start_pc[2];
					for (u2 l = 0; l < 2; ++l){
						start_pc[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					d.start_pc = *start_pc;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t line_number[2];
					for (u2 l = 0; l < 2; ++l){
						line_number[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					d.line_number = *line_number;
					this->current_size+=sizeof(u2);

					lnt_aux.line_number_table[k] = d;
				}

				break;

			case "LocalVariableTable":
				LocalVariableTable_attribute local_aux;

				j = 3;
				for (u2 l = 0; l < 4; ++l){
					attribute_length[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				local_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u4);

				j = 1;
				int8_t local_variable_table_length[2];
				for (u2 l = 0; l < 2; ++l){
					local_variable_table_length[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				local_aux.local_variable_table_length = *local_variable_table_length;
				this->current_size+=sizeof(u2);

				for (int k = 0; k < local_aux.local_variable_table_length; ++k){
					LocalVariableTable_info e;

					j = 1;
					int8_t start_pc[2];
					for (u2 l = 0; l < 2; ++l){
						start_pc[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					e.start_pc = *start_pc;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t length[2];
					for (u2 l = 0; l < 2; ++l){
						length[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					e.length = *length;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t name_index[2];
					for (u2 l = 0; l < 2; ++l){
						name_index[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					e.name_index = *name_index;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t descriptor_index[2];
					for (u2 l = 0; l < 2; ++l){
						descriptor_index[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					e.descriptor_index = *descriptor_index;
					this->current_size+=sizeof(u2);

					j = 1;
					int8_t index[2];
					for (u2 l = 0; l < 2; ++l){
						index[j] = (*this->byte_array + this->current_size + l);
						j--;
					}
					e.index = *index;
					this->current_size+=sizeof(u2);

					local_aux.local_variable_table[k] = e;
				}

				break;

			case "Deprecated":
				Deprecated_attribute dep_aux;

				j = 1;
				for (u2 l = 0; l < 2; ++l){
					attribute_length[j] = (*this->byte_array + this->current_size + l);
					j--;
				}
				dep_aux.attribute_length = *attribute_length;
				this->current_size+=sizeof(u2);

				break;

			default:
				printf("invalido\n");


		}

	}

	return true;
}*/

u2 Leitor::getAcessFlags(){
	return access_flags;
}

u2 Leitor::getThisClass()
{
	return this_class;
}

u2 Leitor::getSuperClass(){
  return super_class;
}

// bool Leitor::setAccessFlagCount() {
// 	int32_t size = 2;
// 	int32_t j = size -1;
// 	int16_t buffer[size];
// 	int16_t access_flags[size];

// 	for (int32_t i = 0; i < size; i++) {
// 		access_flags[j] = *(this->byte_array + this->current_size + i);
// 		j--;
// 	}

// 	memcpy(buffer, &access_flags, sizeof(access_flags));
// 	this->access_flags = *buffer;
// 	this->current_size += sizeof(this->access_flags);
// 	return true;
// }


/* EXIBIDOR */

void Leitor::exibir() {
	printf("Magic number: %x\n", this->magic);
	printf("Minor version: %x\n", this->minor_version);
	printf("Major version: %x\n", this->major_version);
	printf("Constant pool count: %d\n", this->constant_pool_count);
	// printf("Access flags: %x\n", this->access_flags);
}