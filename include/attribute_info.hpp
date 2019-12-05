#ifndef ATTRIBUTEINFO_H
#define ATTRIBUTEINFO_H
#include <cstdint>
#include <iostream>
#include <vector>
#include "cp_info.hpp"
#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

class Attribute_info;
class Code_attribute;

// structs auxiliares
struct ClassInners_info{ 
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
};

struct LineNumber_info{ 
    u2 start_pc;
    u2 line_number;
};
struct ExceptionCode_info{ 
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};
struct LocalVariableTable_info{ 
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
};

// Attributes obrigatorios (dos slides)
class Code_attribute{
    public:
        u2 minor_version;
        u2 attribute_name_index;
        u2 attribute_length;
        u2 max_stack;
        u2 max_locals;
        u4 code_length;
        u1 *code; // u1 code[code_length]
        u2 exception_table_length;
        ExceptionCode_info * exception_table;
        u2 attributes_count;
        Attribute_info * attributes;
        // vector<Attribute_info*> attributes;
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    // public:
        bool set(u4 code_size, u1* byteArray, u2 attribute_name_index);
        // bool setAttribute_name_index(u2 attribute_name_index);
        // bool setAttribute_length(u2 attribute_length);
        // bool setMax_stack(u2  Maxstack);
        // bool setMax_locals(u2 MaxLocals);
        // bool setCode_length(u4 CodeLength);
        // bool setCode(u1 * Code);
        // bool setExceptionTableLength(u2 ExceptTableLength);
        // bool setException_table(u1 * ExceptTable);
        // bool setAttributeCount(u2 AttrCount);
        // u4 setAttributes(u1 * Attrs);
        // bool setCP(Cp_info * ConstantPool);

        // u2 getMax_stack();
        // u2 getMax_locals();
        // u4 getCode_length();
        // u1 *  getCode();
        // u2 getExceptionTableLength();
        // ExceptionCode_info * getExceptionTable();
        // u2 getAttributesCount();
        // Attribute_info * getAttributes();
};
class ConstantValue_attribute{
    private:
        u2 constantvalue_index; // index valido no CP
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável

    public:
        bool setConstantValue(u2 constValue);
        u2 getConstantValue();
        bool setCP(Cp_info * ConstantPool);
};

class Deprecated_attribute{ // attribute OP segundo a  especificação da JVM (OBS: tem no slide nao sei vai pra versao final)
    private:
        //u2 attribute_name_index; valor  no CP = " Deprecated "
        //u4 attribute_length; 
};

class Exceptions_attribute{
    private:
        u2 number_of_exceptions;
        u2 * exception_index_table;// index valido no CP
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        bool setNumber_of_exceptions(u2  NumExceptions);
        bool setExceptionIndexTable(u2 ExceptionIndexTable);
        u2   getNumber_of_exceptions();
        u2 * getExceptionIndexTable(u2 * ExceptionIndexTable);
        bool setCP(Cp_info * ConstantPool);   
};

class InnerClasses_attribute{
    private:
        u2 number_of_classes;
        ClassInners_info * classes;
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        bool setNumber_of_classes();
        bool setClasses(ClassInners_info * Classes);
        u2   getNumber_of_classes();
        bool setCP(Cp_info * ConstantPool);   
};

class SourceFile_attribute {
    private:
        u2 sourcefile_index; // index valido no CP(utf8)
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        bool setSourceFile_index(u2 SourceFile_index);
        u2   getSourceFile_index();
        bool setCP(Cp_info * ConstantPool);   

};

class Synthetic_attribute{ // OBS: nao sei vai para versao final
    private:
        //u2 attribute_name_index; valor  no CP = " Synthetic "
        //u4 attribute_length; 
    public:
};
class LineNumberTable_attribute{
    private:
        u2 line_number_table_length;
        LineNumber_info * line_number_table;
    public:
        bool setLine_number_table_length(u2 Line_num_table_len);
        bool setLine_number_table(LineNumber_info * Line_number_table);
        u2   getLine_number_table_length();
        LineNumber_info * getLine_number_table();

};
class LocalVariableTable_attribute {
    private:
        u2 local_variable_table_length;
        LocalVariableTable_info * local_variable_table;
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        bool setLocal_variable_table_length(u2 local_var_tab_len);
        bool setLocal_variable_table(LocalVariableTable_info * local_var_table);
        u2   getLocal_variable_table_length();
        LocalVariableTable_info * getLocal_variable_table();
        bool setCP(Cp_info * ConstantPool);

};

union info_element{ 
            Code_attribute * codeAttr;
            ConstantValue_attribute * constantValueAttr;
            Deprecated_attribute *  deprecatedAttr;
            Exceptions_attribute * exceptionAttr;
            InnerClasses_attribute * innerClassesAttr;
            SourceFile_attribute *  sourceFileAttr;
            Synthetic_attribute  *  syntheticAttr;
            LineNumberTable_attribute * LineNumberTableAtrr;
            LocalVariableTable_attribute  * LocalVariableTableAttr;
};

class Attribute_info{
    public:
        bool setAttributeNameIndex(u2 attribute_name_index);
        bool setAttributeLength(u4 attribute_length);
        void print();
        bool setInfo(u1* info);
        bool setInfoElement(char* op, info_element* element);

        u2 getAttributeNameIndex();
        u4 getAttributeLength();
        char *getAttributeType();
        u1 *getAttributeInfo();
        bool setCP(Cp_info * ConstantPool);
        u1* getInfo();
        info_element* getInfoElement();
        void printAttributeInfo();
    private:
        u2 attribute_name_index;
        u4 attribute_length;
        info_element* infoElement;
        u1* info;
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
        char * attributeType; // atributo extra para guardar o attributeName recuperado do CP
};
#endif