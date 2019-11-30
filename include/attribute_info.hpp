#ifndef ATTRIBUTEINFO_H
#define ATTRIBUTEINFO_H
#include <cstdint>
#include <iostream>
#include <vector>
#include "cp_info.hpp"
#define u1 uint8_t /**< tipo unsigned int de 8bits*/
#define u2 uint16_t /**< tipo unsigned int de 16bits*/
#define u4 uint32_t /**< tipo unsigned int de 32bits*/

class Attribute_info;
class Code_attribute;


// structs auxiliares
/** struct auxiliar de informações de classe
  possuem informações relacionadas às classes java
*/
struct ClassInners_info{ 
    u2 inner_class_info_index; /**< informação de indice interno da classe*/
    u2 outer_class_info_index; /**< informação de indice externo da classe*/
    u2 inner_name_index; /**< informação do indice do nome interno da classe*/
    u2 inner_class_access_flags;/**< informação referente às flags de acesso da classe*/
};
/** struct auxiliar de informações do numero de linhas da classe java
*/
struct LineNumber_info{ 
    u2 start_pc; /**< Inicio da contagem de linhas*/
    u2 line_number; /**< Número de linhas*/
};
/** struct auxiliar de informações referentes ao código de exceção java
*/
struct ExceptionCode_info{ 
    u2 start_pc; /**< Inicio do bloco de exceção*/
    u2 end_pc; /**< Fim do bloco de exceção*/
    u2 handler_pc; /**< handler do contador de instrução onde ocorreu a exceção*/
    u2 catch_type; /**< Pegador de tipo*/
};
/** struct auxiliar referente à tabela de variavel local
*/
struct LocalVariableTable_info{ 
    u2 start_pc; /**< Inicio do bloco de variaveis*/
    u2 length; /**< Tamanho da variavel local*/
    u2 name_index; /**< name index da variavel local*/
    u2 descriptor_index; /**< descriptor index da variavel local*/
    u2 index; /**< indice da variavel local*/
};

/** \brief classe de identificação de atribuições
* possuem a finalidade de atribuir identificadores de informações do arquivo .class
*/
// Attributes obrigatorios (dos slides)
class Code_attribute{
    public:
        u2 minor_version; /**< atributo referente a versão secundária*/
        u2 attribute_name_index; /**< indice do nome do atributo*/
        u2 attribute_length; /**< tamanho do atributo*/
        u2 max_stack; /**< pilha máxima*/
        u2 max_locals; /**< limite máximo de locais de atributos*/
        u4 code_length; /**< tamanho do código*/
        u1 *code; // u1 code[code_length] /**< ponteiro para o código*/
        u2 exception_table_length; /**< tamanho da tabela de exceção*/
        ExceptionCode_info * exception_table; /**< ponteiro para a tabela de exceção*/
        u2 attributes_count; /**< Contador de atributos*/
        Attribute_info * attributes; /**< ponteiro para os atributos*/
        // vector<Attribute_info*> attributes;
        Cp_info * ConstantPool; /**< CP extra para atributos de tamanho variável*/
        // CP extra para attributes de tamanho variável
    // public:
        /** função set de código de atributo
        *@param code_size tamanho do código
        *@param byteArray tamanho do byte de array
        *@param attribute_name_index indice do nome da atribuição
        *@return retorna verdadeiro em caso de sucesso e falso em caso de falha
        */
        bool set(u4 code_size, u1* byteArray, u2 attribute_name_index);
        // bool setAttribute_name_index(u2 attribute_name_index);
        // bool setAttribute_length(u2 attribute_length);
        // bool setMax_stack(u2  Maxstack);
        // bool setMax_locals(u2 MaxLocals);
        // bool setCode_length(u4 CodeLength);
        // bool setCode(u1 * Code);
        // bool setExceptionTableLength(u2 ExceptTableLength);
        // bool setException_table(u1 * ExceptTable);
        // bool setAttributeCount(u2 AttrCount);
        // u4 setAttributes(u1 * Attrs);
        // bool setCP(Cp_info * ConstantPool);

        // u2 getMax_stack();
        // u2 getMax_locals();
        // u4 getCode_length();
        // u1 *  getCode();
        // u2 getExceptionTableLength();
        // ExceptionCode_info * getExceptionTable();
        // u2 getAttributesCount();
        // Attribute_info * getAttributes();
};
/** Classe de atribuição de constantes
*/
class ConstantValue_attribute{
    private:
        u2 constantvalue_index; // index valido no CP
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável

    public:
        /**Seta um valor constante
        *@param constValue constante a ser setada
        *@return retorna verdadeiro em caso de sucesso ou falso em caso de falha
        */
        bool setConstantValue(u2 constValue);
        /** Pega um valor constante
        *@return a constante armazenada na classe
        */
        u2 getConstantValue();
        /** Seta uma constant pool para atributos de tamanho variável
        *@param ConstantPool referência a constante a ser setada
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setCP(Cp_info * ConstantPool);
};


class Deprecated_attribute{ // attribute OP segundo a  especificação da JVM (OBS: tem no slide nao sei vai pra versao final)
    private:
        //u2 attribute_name_index; valor  no CP = " Deprecated "
        //u4 attribute_length; 
};

/** Classe de exceções de atributos
*/

class Exceptions_attribute{
    private:
        u2 number_of_exceptions;
        u2 * exception_index_table;// index valido no CP
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        /** Seta um número de exceções
        *@param NumExceptions número de exceções
        *@return retorna verdadeiro se o processo for bem sucedido e falso caso contrário
        */
        bool setNumber_of_exceptions(u2  NumExceptions);
        /** Seta um índice da tabela de exceções
        *@param ExceptionIndexTable exceção da tabela indíces que será setado
        *@return retorna verdadeiro se o processo for bem sucedido e falso caso contrário
        */
        bool setExceptionIndexTable(u2 ExceptionIndexTable);
        /** Pega um número de exceções
        *@return retorna o número de exceções armazenadas na classe
        */
        u2   getNumber_of_exceptions();
        /** Pega as exceções armazenadas na classe
        *@return retorna um ponteiro da tabela de exceções de indice
        */
        u2 * getExceptionIndexTable(u2 * ExceptionIndexTable);
        /** Seta uma constant pool para atributos de tamanho variável
        *@param ConstantPool referência a constante a ser setada
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setCP(Cp_info * ConstantPool);   
};

/** Classe de informações referentes a classe interna de atributos
*/

class InnerClasses_attribute{
    private:
        u2 number_of_classes;
        ClassInners_info * classes;
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        /** Seta um número de classes internas
        *@return retorna verdadeiro em caso de sucesso e falso em caso de falha
        */
        bool setNumber_of_classes();
        /** Seta as classes internas
        *@return retorna verdadeiro em caso de sucesso e falso em caso de falha
        */
        bool setClasses(ClassInners_info * Classes);
        /** Pega o número de classes internas setadas
        *@return retorna o número respectivo de classes internas setadas
        */
        u2   getNumber_of_classes();
        /** Seta uma constant pool para atributos de tamanho variável
        *@param ConstantPool referência a constante a ser setada
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setCP(Cp_info * ConstantPool);   
};

/** classe de atribuição de arquivo fonte
*/

class SourceFile_attribute {
    private:
        u2 sourcefile_index; // index valido no CP(utf8)
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        /** Seta um indice de arquivo fonte
        *@param SourceFile_index parâmetro referente ao indice do arquivo fonte
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setSourceFile_index(u2 SourceFile_index);
        /** Pega o indice de arquivo fonte armazenado na classe
        *@return Indice de arquivo fonte
        */
        u2   getSourceFile_index();
        /** Seta uma constant pool para atributos de tamanho variável
        *@param ConstantPool referência a constante a ser setada
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setCP(Cp_info * ConstantPool);   

};

class Synthetic_attribute{ // OBS: nao sei vai para versao final
    private:
        //u2 attribute_name_index; valor  no CP = " Synthetic "
        //u4 attribute_length; 
    public:
};
/** Classe referente à tabela do número de linhas dos atributos
*/
class LineNumberTable_attribute{
    private:
        u2 line_number_table_length;
        LineNumber_info * line_number_table;
    public:
        /** Seta o tamanho da tabela do número de linhas
        *@param Line_num_table_len tamanho da tabela do número de linhas
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setLine_number_table_length(u2 Line_num_table_len);
        /** Seta o número da tabela do número de linhas
        *@param Line_number_table ponteiro referente a informação do número de linhas
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setLine_number_table(LineNumber_info * Line_number_table);
        /** Pega um numero referente ao tamanho da tabela
        *@return numero correspondente
        */
        u2   getLine_number_table_length();
        /** Pega um número referente às linhas da tabela
        *@return retorna uma referência para este número
        */
        LineNumber_info * getLine_number_table();

};
/** Classe referente à tabela de variáveis locais
*/
class LocalVariableTable_attribute {
    private:
        u2 local_variable_table_length;
        LocalVariableTable_info * local_variable_table;
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
    public:
        /** Seta o tamanho referente à tabela de váriaveis locais
        * @param local_var_tab_len tamanho da tabela
        * @return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setLocal_variable_table_length(u2 local_var_tab_len);
        /** Seta a atabela de variávies locais
        * @param local_var_table referência à tabela de variáveis locais
        * @return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setLocal_variable_table(LocalVariableTable_info * local_var_table);
        /** Pega o tamanho da tabela de variáveis locais setado
        * @return tamanho da tabela setada
        */
        u2   getLocal_variable_table_length();
        /** Pega uma referência da tabela de variáveis locais
        * @return referência da tabela setada
        */
        LocalVariableTable_info * getLocal_variable_table();
        /** Seta uma constant pool para atributos de tamanho variável
        *@param ConstantPool referência a constante a ser setada
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setCP(Cp_info * ConstantPool);

};
/** União de elementos relacionadas às informações referêntes aos atributos java
*/
union info_element{ 
            Code_attribute * codeAttr; /**< referência ao código do atributo*/
            ConstantValue_attribute * constantValueAttr; /**< referência à constante de atribuição*/
            Deprecated_attribute *  deprecatedAttr; /**< referência aos atributos depreciados java*/
            Exceptions_attribute * exceptionAttr; /**< referência aos atributos de exceções java*/
            InnerClasses_attribute * innerClassesAttr; /**< referência ao atributo de classes internas java*/
            SourceFile_attribute *  sourceFileAttr; /**< referência ao arquivo de atribuições*/
            Synthetic_attribute  *  syntheticAttr; /**< referência aos atributos sintéticos*/
            LineNumberTable_attribute * LineNumberTableAtrr; /**< referência à tabela de número de linhas*/
            LocalVariableTable_attribute  * LocalVariableTableAttr; /**< referência à tabela de váriaveis locais*/
};
/** Classe referênte às informações de atributos
*/
class Attribute_info{
    public:
        /** Seta um indíce de nome de um atributo
        * @param attribute_name_index atributo referente ao indice relacionado ao nome do atributo
        * @return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setAttributeNameIndex(u2 attribute_name_index);
        /** Seta o tamanho de um atributo
        * @param attribute_length tamanho do atributo a ser setado
        * @return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setAttributeLength(u4 attribute_length);
        /** Função que printa os valores da classe de atributos
        */
        void print();
        //bool setAttributeType(char * attribute_name_index);// seta info e attributeType
        // u4 setInfo(char *typeAttribute, u1 sizeTypeAtrr, u1 * infoAttr);// seta info e attributeType(OBS: retorna o numero de bytes percorridos)
        /** Seta à informação referente ao atributo
        * @param info referência à informação relacionada ao atributo
        * @return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setInfo(u1* info);
        /** Seta a informação do tipo relacionado ao atributo
        * @param op operação relacionada a informação do elemento
        * @param element referência relacionada a informação do elemento
        * @return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setInfoElement(char* op, info_element* element);
        /** Pega o valor do indce setado do nome do atributo
        * @return retorna o índice do nome de atribuição setado
        */
        u2 getAttributeNameIndex();
        /** Pega o tamanho do atributo setado
        * @return tamanho do atributo a ser retornado
        */
        u4 getAttributeLength();
        /** Pega o tipo de atributo setado
        * @return tipo a ser retornado
        */
        char *getAttributeType();
        /** Pega informações referêntes ao atributo setado
        * @return informação retornada
        */
        u1 *getAttributeInfo();
        /** Seta uma constant pool para atributos de tamanho variável
        *@param ConstantPool referência a constante a ser setada
        *@return retorna um valor verdadeiro em caso de sucesso no processo ou falso caso contrário
        */
        bool setCP(Cp_info * ConstantPool);
        /** Pega a referência relacionada à(s) informação(ões) da classe de atributos
        * @return referência das informações
        */
        u1* getInfo();
        /** Pega a referência relacionada às informações dos elementos da classe de atributos
        * @return retorna a referência das informações dos elementos
        */
        info_element* getInfoElement();
    private:
        u2 attribute_name_index;
        u4 attribute_length;
        info_element* infoElement;
        u1* info;
        Cp_info * ConstantPool; // CP extra para attributes de tamanho variável
        char * attributeType; // atributo extra para guardar o attributeName recuperado do CP
};
#endif