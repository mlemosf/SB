#ifndef METHODINFO_H
#define METHODINFO_H
#include <cstdint>
#include <iostream>
#include <vector>
#include "attribute_info.hpp"

class Method_info{
    public:
        bool setAcessFlags(u2 access_flags);
        bool setNameIndex(u2 name_index);
        bool setDescriptorIndex(u2 descriptor_index);
        bool setAttributeCount(u2 attributes_count);
        bool setAttributes(Attribute_info * attributes);

        u2 getAcessFlags();
        u2 getNameIndex();
        u2 getDescriptorIndex();
        u2 getAttributeCount();
        Attribute_info * getAttributes();
    private:
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        Attribute_info * attributes; //attribute_info attributes[attributes_count];
};
#endif