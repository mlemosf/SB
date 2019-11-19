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

	int32_t size = this->constant_pool_count - 1;
	int32_t count = 0;
	int8_t tag;
	int32_t ret = 0;
	int32_t pos = 0;
	int32_t utf8_size = 0;
	Cp_info *cp_info = new Cp_info();

	for (int32_t i = 0; i < size; i++) {
		tag = *(this->byte_array + this->current_size + pos);
		utf8_size = *(this->byte_array + this->current_size + pos + 2);
		ret = cp_info->getConstantPoolTag(tag, utf8_size);
		cp_info->addElement(tag, ret, pos, this->current_size,  this->byte_array);
		pos += ret;
		count += ret;
	}
	this->constant_pool = cp_info;
	this->constant_pool->getConstantPool();
	this->current_size += count;
	return true;
}

u2 Leitor::getAccessFlags(){
	return this->access_flags;
}

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

u2 Leitor::getThisClass(){return this->this_class;}

bool Leitor::setThisClass(){
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

u2 Leitor::getSuperClass(){return this->super_class;}

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

u2 Leitor::getInterfacesCount(){return interfaces_count;}

bool Leitor::setInterfacesCount(){
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

u2 * Leitor::getInterfaces(){return this->interfaces;} 

bool Leitor::setInterfaces(){
	int32_t size = this->attributes_count;
	int32_t j = size;
	u2 interfaces[size];
	u2 buffer[size];
	u1 aux[1];
	for(int i=0;i< size-1; i++){
		aux[0] = *(this->byte_array + this->current_size + i);
		aux[1] = *(this->byte_array + this->current_size + i+1);
		interfaces[j] = aux[0] + aux[1];
		j--;
	}
	this->interfaces = interfaces;
	return true;
}

u2 Leitor::getFieldsCount(){return fields_count;}

bool Leitor::setFieldsCount(){
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

void Leitor::printAccessFlags(){
	char access[20];
	switch (this->access_flags)
	{
	case ACC_PUBLIC:
		memcpy(&access,"ACC_PUBLIC",sizeof("ACC_PUBLIC"));
		break;
	case ACC_FINAL:
		memcpy(&access,"ACC_FINAL",sizeof("ACC_FINAL"));
		break;
	case ACC_SUPER:
		memcpy(&access,"ACC_SUPER",sizeof("ACC_SUPER"));
		break;
	case ACC_INTERFACE:
		memcpy(&access,"ACC_INTERFACE",sizeof("ACC_INTERFACE"));
		break;
	case ACC_ABSTRACT:
		memcpy(&access,"ACC_ABSTRACT",sizeof("ACC_ABSTRACT"));
		break;
	case ACC_SYNTHETIC:
		memcpy(&access,"ACC_SYNTHETIC",sizeof("ACC_SYNTHETIC"));
	case ACC_ANNOTATION:
		memcpy(&access,"ACC_ANNOTATION",sizeof("ACC_ANNOTATION"));
		break;
	default:
		break;
	}
	printf("Access Flags: %x %s \n",this->access_flags,access);
}
void Leitor::printThisClass(){ // completar depois para buscar do CP
	printf("ThisClass: %x\n", this->this_class);
}
void Leitor::printSuperClass(){ // completar depois para buscar do CP
	printf("SuperClass: %x\n", this->super_class);
}
void Leitor::printInterfaceCont(){
	printf("Interfaces Count : %x\n", this->interfaces_count);
}
void Leitor::printInterfaces(){
	if(this->interfaces_count!=0){
		printf("Interfaces: ");
		for(int i=0;i<this->interfaces_count;i++){
			printf("%x ",this->interfaces[i]);
		}
		printf("\n");
	}
}
/*vector<Field_info> Leitor::getFields(){
	vector<Field_info> ret;

	for (u2 i = 0; i < this->fields_count; ++i){
		ret.push_back(this->fields[i]);
	}

	return ret;
}

bool Leitor::setFields(){
	uint16_t size = this->fields_count;
	vector<Field_info> fields;
	vector<Attribute_info> attributes;
	Field_info aux;
	u2 access_flags;
	u2 nameIndex;
	u2 descriptor_index;
	u2 attributes_count;
	for(int i=0;i<size;i++){
		access_flags = read2byte();
		fields[i].setAcessFlags(access_flags);
		nameIndex = read2byte();
		fields[i].setNameIndex(nameIndex);
		descriptor_index = read2byte();
		fields[i].setDescriptorIndex(descriptor_index);
		attributes_count = read2byte();
		fields[i].setAttributesCount(attributes_count);
		for(int j=0;j<attributes_count;j++){
			// precisa terminar o attribute_info (Voltar aqui)
		}
	}
	return true;
}*/

/*bool Leitor::setFields(){ // refatora depois conferir attributes
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
		*buffer = read2byte();
		fields[i].setAcessFlags(*buffer);
		*buffer = read2byte();
		fields[i].setNameIndex(*buffer);
		*buffer = read2byte();
		fields[i].setDescriptorIndex(*buffer);
		*buffer = read2byte();
		fields[i].setAttributesCount(*buffer);
		for(int32_t k=0;k < this->attributes_count;k++){
			attributes[k].setAttributeNameIndex(read2byte());
			attributes[k].setAttributeLength(read2byte());
			attributes[k].setInfo(this->byte_array);	
		}
		fields[i].setAttributes(attributes);
	}
	return true;
}*/

u2 Leitor::getMethodsCount(){
	return methods_count;
}


/*u2 Leitor::getAttributesCount(){return attributes_count;}

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
	int16_t access_flags;
	int16_t name_index;
	int16_t descriptor_index;
	int16_t attributes_count;

	for (int i = 0; i < this->methods_count; ++i){
		Method_info a;
		access_flags = read2byte();
		a.setAccessFlags(access_flags);

		//printf("access_flags: 0x%04x\n", *access_flags);
		name_index = read2byte();
		a.setNameIndex(name_index);
		
		descriptor_index = read2byte();
		a.setDescriptorIndex(descriptor_index);
		
		attributes_count = read2byte();
		a.setAttributeCount(attributes_count);

		a.setAttributes(this->constant_pool);
	
		this->methods[i] = a;
	}
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

bool Leitor::setAttributes(){
	int32_t size = 2;
	u4 j = size-1;
	int16_t attribute_name_index;
	int32_t attribute_length;

	for (u4 i = 0; i < this->attributes_count; ++i){
		attribute_name_index = read2byte();
		attribute_length = read4byte();


		string op = "";
		u2 length = this->constant_pool.constant_pool[attribute_name_index].c11.length;
		for (int i = 0; i < length; ++i){
			op += constant_pool.constant_pool[attribute_name_index].c11.bytes[i];
		}

		switch(op){
			case "ConstantValue":
				ConstantValue_attribute cv_aux;
				cv_aux.attribute_name_index = attribute_name_index;
				cv_aux.attribute_length = attribute_length;
				cv_aux.constantvalue_index = read2byte();
				this->attributes[i] = cv_aux;
				break;
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

				code_aux.setAttributes(this->constant_pool);
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

			case "InnerClasses":
				InnerClasses_attribute in_aux;
				in_aux.attribute_name_index = attribute_name_index;
				in_aux.attribute_length = attribute_length;

				in_aux.number_of_classes = read2byte();
				

				for (int k = 0; k < in_aux.number_of_classes; ++k){
					ClassInners_info c;
					
					c.inner_class_info_index = read2byte();
					c.outer_class_info_index = read2byte();
					c.inner_name_index = read2byte();
					c.inner_class_access_flags = read2byte();

					in_aux.classes[k] = c;	
				}
				this->attributes[i] = in_aux;
				break;

			case "Synthetic":
				Synthetic_attribute syn_aux;
				syn_aux.attribute_name_index = attribute_name_index;
				syn_aux.attribute_length = attribute_length;

				this->attributes[i] = syn_aux;
				break;

			case "SourceFile":
				SourceFile_attribute source_aux;
				source_aux.attribute_name_index = attribute_name_index;
				source_aux.attribute_length = attribute_length;

				source_aux.sourcefile_index = read2byte();

				this->attributes[i] = source_aux;
				break;
			
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

			case "Deprecated":
				Deprecated_attribute dep_aux;
				dep_aux.attribute_name_index = attribute_name_index;
				dep_aux.attribute_length = attribute_length;

				this->attributes[i] = dep_aux;
				break;

			default:
				printf("invalido\n");

		}

	}

	return true;
}

vector<Method_info> Leitor::getMethods(){
	vector<Method_info> ret;

	for (u2 i = 0; i < this->methods_count; ++i){
		ret.push_back(this->methods[i]);
	}

	return ret;
}

vector<Attribute_info> Leitor::getAttributes(){
	vector<Attribute_info> ret;

	for (u2 i = 0; i < this->attributes_count; ++i){
		ret.push_back(this->attributes[i]);
	}

	return ret;
}*/

/* EXIBIDOR */

void Leitor::exibir() {
	printf("Magic number: %x\n", this->magic);
	printf("Minor version: %x\n", this->minor_version);
	printf("Major version: %x\n", this->major_version);
	printf("Constant pool count: %d\n", this->constant_pool_count);
	printf("Constant Pool:\n");
}