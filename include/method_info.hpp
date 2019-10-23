#ifndef METHODINFO_H
#define METHODINFO_H
#include <cstdint>
#include <iostream>
#include <vector>
#include "attribute_info.hpp"

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL 0x0010
#define ACC_SYNCHRONIZED 0x0020
#define ACC_BRIDGE 0x0040
#define ACC_VARARGS 0x0080
#define ACC_NATIVE 0x0100
#define ACC_ABSTRACT 0x0400
#define ACC_STRICT 0x0800
#define ACC_SYNTHETIC 0x1000

class Method_info{
    private:
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        Attribute_info * attributes; //attribute_info attributes[attributes_count];
    public:
        bool setAccessFlags(u2 access_flags);
        bool setNameIndex(u2 name_index);
        bool setDescriptorIndex(u2 descriptor_index);
        bool setAttributeCount(u2 attributes_count);
        void print();
        bool setAttributes();

        u2 getAccessFlags();
        u2 getNameIndex();
        u2 getDescriptorIndex();
        u2 getAttributeCount();
        Attribute_info * getAttributes();

};
#endif