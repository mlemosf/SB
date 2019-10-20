#ifndef METHODINFO_H
#define METHODINFO_H
#include <cstdint>
#include <iostream>
#include <vector>
#include "attribute_info.hpp"

class Method_info{
    public:
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