#ifndef ATTRIBUTEINFO_H
#define ATTRIBUTE_H
#include <cstdint>
#include <iostream>
#include <vector>

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t
class Attribute_info{
    public:
        bool setAttributeNameIndex(u2 attribute_name_index);
        bool setAttributeLenght(u2 attribute_length);
        bool setInfo(u1 * info);

        u2 getAttributeNameIndex();
        u2 getAttributeLenght();
        u1* getInfo();
    private:
        u2 attribute_name_index;
        u2 attribute_length;
        u1 * info;    //u1 info[attribute_length];
};

#endif