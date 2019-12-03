#ifndef FIELDINFO_H
#define FIELDINFO_H
#include <cstdint>
#include <iostream>
#include <vector>
#include "attribute_info.hpp"

//#define u1 uint8_t
//#define u2 uint16_t
//#define u4 uint32_t


#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL  0x0010
#define ACC_SUPER 0x0020
#define ACC_VOLATILE 0x0040
#define ACC_TRANSIENT 0x0080
#define ACC_SYNTHETIC 0x1000
#define ACC_ENUM      0x4000
#define ACC_INTERFACE 0x0200
#define ACC_ABSTRACT 0x0400
#define ACC_ANNOTATION 0x2000
using namespace std;

/** Classe de informações de campo
Com ela é possível manipular dados referentes aos campos da JVM
*/
class Field_info{
    public:
    				/** Método para setar uma flag de acesso
						@param acess_flags flag a ser setada
						@return retorna um valor de sucesso caso seja setado ou falso caso contrário
    				*/
            bool setAcessFlags(u2 acess_flags);
            /** Método para setar um indice de nome
						@param name_index indice de nome a ser setado
						@return retorna um valor de sucesso caso seja setado ou falso caso contrário
    				*/
            bool setNameIndex(u2 name_index);
            /** Método para setar um descritpr de indices
						@param descriptor_index indice do descritor a ser setado
						@return retorna um valor de sucesso caso seja setado ou falso caso contrário
    				*/
            bool setDescriptorIndex(u2 descriptor_index);
            /** Método para setar o contador de atributos
						@param attributes_count contador a ser setado
						@return retorna um valor de sucesso caso seja setado ou falso caso contrário
    				*/
            bool setAttributesCount(u2 attributes_count);
            /** Método para setar Atributos
						@param attributes referência aos atributos a serem colocados 
						@return retorna um valor de sucesso caso seja setado ou falso caso contrário
    				*/
            bool setAttributes(Attribute_info * attributes);

            /** Método para pegar uma flag de acesso
						@return retorna o valor setado na classe
    				*/
            u2 getAcessFlags();
            /** Método para pegar um indice de nome
						@return retorna o valor setado na classe
    				*/
            u2 getNameIndex();
            /** Método para pegar um descritor de indice
						@return retorna o valor setado na classe
    				*/
            u2 getDescriptorIndex();
            /** Método para pegar um contador de atributos
						@return retorna o valor setado na classe
    				*/
            u2 getAttributesCount();
            /** Método para pegar atributos
						@return retorna os valores setado na classe
    				*/
            Attribute_info * getAttributes();
            /** Método para imprimir valores da classe
						*/
            void print();

    private:
            u2 access_flags;
            u2 name_index;
            u2 descriptor_index;
            u2 attributes_count;
            Attribute_info * attributes; //Attribute_info attributes[attributes_count];
};


#endif