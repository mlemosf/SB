#ifndef ATTRIBUTEINFO_H
#define ATTRIBUTEINFO_H
#include <cstdint>
#include <iostream>
#include <vector>
#include "cp_info.hpp"
#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

class Attribute_info{
    public:
        bool setAttributeNameIndex(u2 attribute_name_index);
        bool setAttributeLength(u4 attribute_length);
        void print();
        //bool setAttributeType(char * attribute_name_index);// seta info e attributeType
        bool setInfo(char * typeAttribute, u1 * infoAttr);// seta info e attributeType

        u2 getAttributeNameIndex();
        u4 getAttributeLength();
        char * getAttributeType();
        u1 * getAttributeInfo();
    private:
        u2 attribute_name_index;
        u4 attribute_length;
        union info{ 
            Code_attribute codeAttr;
            ConstantValue_attribute constantValueAttr;
            Deprecated_attribute  deprecatedAttr;
            Exceptions_attribute  exceptionAttr;
            InnerClasses_attribute innerClassesAttr;
            SourceFile_attribute   sourceFileAttr;
            Synthetic_attribute    syntheticAttr;
            LineNumberTable_attribute LineNumberTableAtrr;
            LocalVariableTable_attribute LocalVariableTableAttr;
        };
        char * attributeType; // atributo extra para guardar o attributeName recuperado do CP
};

// Attributes obrigatorios (dos slides)
class Code_attribute{
    private:
        u2 max_stack;
        u2 max_locals;
        u4 code_length;
        u1 * code; // u1 code[code_length]
        u2 exception_table_length;
        ExceptionCode_info * exception_table;
        u2 attributes_count;
        Attribute_info * attributes;
    public:
        bool setMax_stack(u2  Maxstack);
        bool setMax_locals(u2 MaxLocals);
        bool setCode_length(u4 CodeLength);
        bool setCode(u1 * Code);
        bool setExceptionTableLength(u2 ExceptTableLength);
        bool setExceptionCode_info(ExceptionCode_info * ExceptTable);
        bool setAttributeCount(u2 AttrCount);
        bool setAttributes(Attribute_info * Attrs);

        u2 getMax_stack();
        u2 getMax_locals();
        u4 getCode_length();
        u1 *  getCode();
        u2 getExceptionTableLength();
        ExceptionCode_info * getExceptionTable();
        u2 getAttributesCount();
        Attribute_info * getAttributes();
};
class ConstantValue_attribute{
    private:
        u2 constantvalue_index; // index valido no CP
    public:
        bool setConstantValue(u2 constValue);
        u2 getConstantValue();
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
    public:
        bool setNumber_of_exceptions(u2  NumExceptions);
        bool setExceptionIndexTable(u2 ExceptionIndexTable);
        u2   getNumber_of_exceptions();
        u2 * getExceptionIndexTable(u2 * ExceptionIndexTable);   
};

class InnerClasses_attribute{
    private:
        u2 number_of_classes;
        ClassInners_info * classes;
    public:
        bool setNumber_of_classes();
        bool setClasses(ClassInners_info * Classes);
        u2   getNumber_of_classes();
};

class SourceFile_attribute {
    private:
        u2 sourcefile_index; // index valido no CP(utf8)
    public:
        bool setSourceFile_index(u2 SourceFile_index);
        u2   getSourceFile_index();

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
    public:
        bool setLocal_variable_table_length(u2 local_var_tab_len);
        bool setLocal_variable_table(LocalVariableTable_info * local_var_table);
        u2   getLocal_variable_table_length();
        LocalVariableTable_info * getLocal_variable_table();

};

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
#endif