#ifndef ATTRIBUTEINFO_H
#define ATTRIBUTEINFO_H
#include <cstdint>
#include <iostream>
#include <vector>

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

class Attribute_info{
    public:
        bool setAttributeNameIndex(u2 attribute_name_index);
        bool setAttributeLength(u4 attribute_length);
        bool setInfo(u1 * info);
        void print();

        u2 getAttributeNameIndex();
        u4 getAttributeLength();
        u1* getInfo();
    private:
        u2 attribute_name_index;
        u4 attribute_length;
        u1 * info;    //u1 info[attribute_length];
};

class ClassInners_info{ // classe extra
    public:
        u2 inner_class_info_index;
        u2 outer_class_info_index;
        u2 inner_name_index;
        u2 inner_class_access_flags;
};
class LineNumber_info{ // classe extra
    public:
        u2 start_pc;
        u2 line_number;
};
class ExceptionCode_info{ // classe extra
    public:
        u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
};
class LocalVariableTable_info{ // classe extra
    public:
        u2 start_pc;
        u2 length;
        u2 name_index;
        u2 descriptor_index;
        u2 index;
};
class Code_attribute : public Attribute_info{
    public:
        u2 attribute_name_index; // index no constant_pool com index = "Code"
        u2 attribute_length;
        u2 max_stack;
        u2 max_locals;
        u4 code_length;
        u1 * code; //u1 code[code_length];
        u2 exception_table_length;
        ExceptionCode_info * exception_table;
        u2 attributes_count;
        Attribute_info * attributes;

        //bool setAttributes(Cp_info constant_pool);
};
class ConstantValue_attribute : public Attribute_info{
    public:
        u2 attribute_name_index; // elemento Constant_utf8 no Constant_pool
        u2 attribute_length;   // sempre 2
        u2 constantvalue_index;
};
class Deprecated_attribute : public Attribute_info{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
};
class Exceptions_attribute : public Attribute_info{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
        u2 number_of_exceptions;
        u2 * exception_index_table;//u2 exception_index_table[number_of_exceptions];
};
class InnerClasses_attribute : public Attribute_info{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
        u2 number_of_classes;
        ClassInners_info * classes;
};
class SourceFile_attribute : public Attribute_info{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
        u2 sourcefile_index;

};
class Synthetic_attribute : public Attribute_info{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
};
class LineNumberTable_attribute : public Attribute_info{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
        u2 line_number_table_length;
        LineNumber_info * line_number_table;

};
class LocalVariableTable_attribute : public Attribute_info{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
        u2 local_variable_table_length;
        LocalVariableTable_info * local_variable_table;
};

#endif