#include "../include/field_info.hpp"
using namespace std;


// bool Field_info::setAcessFlags(u2 accessFlags){
//     this->access_flags = accessFlags;
//     return true;
// }
// bool Field_info::setNameIndex(u2 nameIndex){
//     this->name_index = nameIndex;
//     return true;
// }
// bool Field_info::setAttributesCount(u2 attributeCount){
//     this->attributes_count = attributeCount;
//     return true;
// }
// bool Field_info::setDescriptorIndex(u2 descriptorIndex){
//     this->descriptor_index = descriptorIndex;
//     return true;
// }
// bool Field_info::setAttributes(Attribute_info * Attributes){
//     for(int32_t i=0;i<this->attributes_count;i++){
//         this->attributes[i] = Attributes[i];
//     }
//     return true;
// }

bool Field_info::setFields(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count) {
    field_info_element *element = (field_info_element*)malloc(sizeof(field_info_element));
    element->access_flags = access_flags;
    element->name_index = name_index;
    element->descriptor_index = descriptor_index;
    element->attributes_count = attributes_count;
    this->fields.push_back(element);
    return true;
}

// void Field_info::print(){
//     printf("Name Index: %d\n",name_index);
//     printf("Descriptor Index: %d\n",descriptor_index);
//     printf("Acess Flags: %x",access_flags);
//     switch(access_flags){
//         case ACC_PUBLIC:
//           printf("[public]");
//           break;
//     case ACC_PRIVATE:
//       printf("[private]");
//       break;
//         case ACC_PROTECTED:
//           printf("[protected]");
//           break;
//         case ACC_STATIC:
//           printf("[static]");
//           break;
//         case ACC_FINAL:
//           printf("[final]");
//           break;
//         case ACC_VOLATILE:
//           printf("[volatile]");
//           break;
//         case ACC_TRANSIENT:
//           printf("[transient]");
//           break;
//         case ACC_SYNTHETIC:
//           printf("[synthetic]");
//           break;
//         case ACC_ENUM:
//           printf("[enum]");
//           break;
//     }
//     printf("\n");
// }

// u2 Field_info::getAcessFlags(){return this->access_flags;}
// u2 Field_info::getAttributesCount(){return this->attributes_count;}
// u2 Field_info::getDescriptorIndex(){return this->descriptor_index;}
// u2 Field_info::getNameIndex(){return this->name_index;}
// Attribute_info * Field_info::getAttributes(){return this->attributes;}
// 

void Field_info::printFieldsInfo() {
    vector<field_info_element*>::iterator i;
    int j = 0;
    // printf("%d\n", this->fields)
    for (i = this->fields.begin(); i != this->fields.end(); ++i) {
      // printf("here\n");
        printf("========== [%d] ===========\n", j);
        printf("Name: %d\n", (*i)->name_index);
        printf("Descriptor index: %d\n", (*i)->descriptor_index);
        printf("Access flags: 0x000%x\n", (*i)->access_flags);
        j++;
    }
}