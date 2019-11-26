#include "../include/leitor.hpp"
#include "../include/field_info.hpp"
#include  "field_info.cpp"
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
	this->minor_version = read2byte();
	return true;
}

u2 Leitor::getMinorVersion(){return this->minor_version;}

bool Leitor::setMajorVersion() {
	this->major_version = read2byte();
	return true;
}

u2 Leitor::getMajorVersion(){return this->major_version;}

bool Leitor::setConstantPoolCount() {
	this->constant_pool_count = read2byte();
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
		if (tag == 6) {
			cp_info->addElement(66, 0, 0, 0, 0);
		}
		pos += ret;
		count += ret;
	}
	this->constant_pool = cp_info;
	this->constant_pool->getConstantPool();
	this->current_size += count;
	return true;
}
Cp_info * Leitor::getConstantPool(){
	return this->getConstantPool();
}
u2 Leitor::getAccessFlags(){
	return this->access_flags;
}

bool Leitor::setAccessFlags() {
	this->access_flags = read2byte();
	return true;
}

u2 Leitor::getThisClass(){return this->this_class;}

bool Leitor::setThisClass(){
	this->this_class= read2byte();
	return true;
}

u2 Leitor::getSuperClass(){return this->super_class;}

bool Leitor::setSuperClass() {
	this->super_class = read2byte();
	return true;
}

u2 Leitor::getInterfacesCount(){return interfaces_count;}

bool Leitor::setInterfacesCount(){
	this->interfaces_count = read2byte();
	return true;
}

u2 * Leitor::getInterfaces(){return this->interfaces;} 

bool Leitor::setInterfaces(){
	int32_t size = this->interfaces_count;
	u2  buffer;
	u2 interfaces[size];
	for(int i=0;i < size; i++){
		buffer = read2byte(); 
		interfaces[i] = buffer;
	}
	this->interfaces = (u2*)malloc(sizeof(interfaces));
	for(int i=0;i<size;i++){
		this->interfaces[i] = interfaces[i];
	}
	return true;
}

u2 Leitor::getFieldsCount(){return this->fields_count;}

bool Leitor::setFieldsCount(){
	this->fields_count = read2byte();
	return true;
}
bool Leitor::setFields(){ 
	Field_info  buffer;
	Attribute_info attributeAux;
	cp_info cpInfoAux;
	u2 lengthNameIndex;
	char nameIndexAttribute[50];
	for(int i=0;i<this->fields_count;i++){
		buffer.setAcessFlags(read2byte());
		buffer.setNameIndex(read2byte());
		buffer.setDescriptorIndex(read2byte());
		buffer.setAttributesCount(read2byte());
		for(int j=0;j< buffer.getAttributesCount();j++){ // read attributes
			attributeAux.setCP(this->constant_pool);
			attributeAux.setAttributeNameIndex(read2byte());
			attributeAux.setAttributeLength(read4byte());
			// set info
			cpInfoAux = this->constant_pool->getCpInfoElement(read2byte());
			lengthNameIndex = cpInfoAux.constant_element.c11->length;
			strcpy(nameIndexAttribute,(const char *)cpInfoAux.constant_element.c11->bytes);
			nameIndexAttribute[lengthNameIndex]= '\0';
			this->current_size+=attributeAux.setInfo(nameIndexAttribute,lengthNameIndex,this->byte_array + this->constant_pool_count);
		}
	}
	return true;
}
// Exibidor
void Leitor::printAccessFlags(){
	uint16_t flags = (uint16_t)this->getAccessFlags();
	uint8_t bits1 = flags & 0x000F;
	uint8_t bits2 = flags & 0x00F0;
	uint8_t bits3 = flags & 0x0F00;
	uint8_t bits4 = flags & 0xF000;
	printf("Access Flags: ");
	if(bits1 == ACC_PUBLIC){
		printf("[ACC_PUBLIC] ");
	}else printf("[ACC_UNKNOWN] ");

	if(bits2!=0){
		if(bits2==ACC_FINAL) printf("[ACC_FINAL] ");
		else if(bits2==ACC_SUPER) printf("[ACC_SUPER] ");
		else printf("[ACC_UNKNOWN] ");
	}
	if(bits3!=0){
		if(bits3==ACC_INTERFACE) printf("[ACC_INTERFACE] ");
		else if(bits3==ACC_ABSTRACT) printf("[ACC_ABSTRACT] ");
		else printf("[ACC_UNKNOWN] ");
	}
	if(bits4!=0){
		if(bits4==ACC_SYNTHETIC) printf("[ACC_SYNTHETIC] ");
		else if(bits4==ACC_ANNOTATION) printf("[ACC_ANNOTATION] ");
		else if(bits4==ACC_ENUM) printf("[ACC_ENUM] ");
		else printf("[ACC_UNKNOWN] ");
	}
	printf("\n");
}
void Leitor::printThisClass(){ // completar depois:fazer  buscar dos nomes no CP
	printf("ThisClass: %x\n", this->getThisClass());
}
void Leitor::printSuperClass(){ // completar depois:fazer  buscar dos nomes no CP
	printf("SuperClass: %x\n", this->getSuperClass());
}
void Leitor::printInterfaceCont(){
	printf("Interfaces Count : %x\n", this->getInterfacesCount());
}
void Leitor::printInterfaces(){
	if(this->interfaces_count!=0){
		printf("Interfaces[0..%d]: ",this->interfaces_count-1);
		for(int i=0;i<this->interfaces_count;i++){
			printf("%d ",this->interfaces[i]);
		}
		printf("\n");
	}
}
void Leitor::printFieldsCount(){
	printf("FieldsCount: %x\n",this->fields_count);
}
vector<Field_info> Leitor::getFields(){
	vector<Field_info> ret;

	for (u2 i = 0; i < this->fields_count; ++i){
		ret.push_back(this->fields[i]);
	}
	return ret;
}

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

/*Set e Get*/

bool set(int key)
{
	switch(key)
	{
		case MAGIC_NUMBER:
		  return setMagicNumber();
		case MINOR_VERSION:
		  return setMinorVersion();
		case MAJOR_VERSION:
		  return setMajorVersion()
		case CONSTANT_POOL_COUNT:
			return setConstantPoolCount();
		case CONSTANT_POOL:
			return setConstantPool();
		case ACCESS_FLAGS:
			return setAccessFlags();
		case THIS_CLASS:
			return setThisClass();
		case SUPER_CLASS:
			return setSuperClass();
		case INTERFACES_COUNT:
			return setInterfacesCount();
		case INTERFACES:
			return setInterfaces();
		case FIELDS:
			return setFieldsCount();
		case FIELDS_COUNT:
			return setFields();
		case METHODS:
			return setMethodsCount();
		case METHODS_COUNT:
			return setMethods();
		case ATTRIBUTES_COUNT:
			return setAttributesCount();
		case ATTRIBUTES:
			return setAttributes();
	}
	return false;
}

u2 get(int key)
{
	switch(key)
	{
		case INTERFACES_COUNT:
			return getInterfacesCount();
		case MINOR_VERSION:
			return getMinorVersion();
		case MAJOR_VERSION:
			return getMajorVersion();
		case CONSTANT_POOL_COUNT:
			return getConstantPoolCount();
		case FIELDS_COUNT:
			return getFieldsCount();
		case METHODS_COUNT:
			return getMethodsCount();
		case ATTRIBUTES_COUNT:
			return getAttributesCount();
		case ACCESS_FLAGS:
			return getAccessFlags();
		case SUPER_CLASS:
			return getSuperClass();
		case THIS_CLASS:
			return getThisClass();
	}
	return 0;
}

/* EXIBIDOR */

void Leitor::exibir() {
	char nameIndex[50];
	int aux;
	printf("Magic number: %x\n", this->magic);
	printf("Minor version: %x\n", this->minor_version);
	printf("Major version: %x\n", this->major_version);
	printf("Constant pool count: %d\n", this->constant_pool_count);
	cp_info e = this->constant_pool->getCpInfoElement(9); 
	aux = e.constant_element.c11->length;
	strcpy(nameIndex,(const char *)e.constant_element.c11->bytes);
	nameIndex[aux]='\0';
	printf("String do elemento 10 do cp: %s\n", nameIndex);
}