#ifndef FIELDINFO_H
#define FIELDINFO_H
#include <cstdint>
#include <iostream>
#include <vector>

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL  0x0010
#define ACC_VOLATILE 0x0040
#define ACC_TRANSIENT 0x0080
#define ACC_SYNTHETIC 0x1000
#define ACC_ENUM      0x4000
using namespace std;

class Fiel_info{
    public:
            u2 getAcessFlags();
            u2 getNameIndex();
            u2 getDescriptorIndex();
            u2 getAttributesCount;

    private:
            u2 access_flags;
            u2 name_index;
            u2 descriptor_index;
            u2 attributes_count;
            // attribute_info attributes[attributes_count];
};


#endif