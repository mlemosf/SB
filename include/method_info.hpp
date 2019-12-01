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

/**
@struct method_info_element estrutura de informações relacionadas aos métodos Java
*/
struct method_info_element {
    u2 access_flags; /**< flags de acesso*/
    u2 name_index; /**< indice de nome*/
    u2 descriptor_index; /**< descritor de indice*/
    u2 attributes_count; /**< contador de atributos*/
    Attribute_info *attributes; /**< atributos dos metodos*///attribute_info attributes[attributes_count];
};

/** Classe de informações relacionados aos métodos Java
Com ela é possível manipular dados referentes aos métodos da JVM
*/

class Method_info{
    public:
        vector<method_info_element*> methods; /**< vetor de informações de métodos*/
        /** Função para setar campos
        @param acess_flags flags de acesso do campo a ser setado
        @param name_index indice do nome do campo a ser setado
        @param descriptor_index descritor de indice referente ao campo
        @param attributes_count atributos contados referentes ao campo
        @param attributes atributos relacionados ao campo
        @return retorna verdadeiro em caso de sucesso ou falso em caso de falha
        */
        bool setFields(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count, Attribute_info* attributes);
        /** Função get para pegar as informações relacionadas aos métodos
        @param index indíce relacionada a informação a ser pega
        @return retorna uma referência as informações relacionadas aos elementos de um método
        */
        method_info_element* getMethod(u2 index);
        /** Função que pega informações relacionadas à metodos e armazena na classe
        */
        void getMethodInfo();
};
#endif