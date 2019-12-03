#ifndef CPINFO_H
#define CPINFO_H

#include <cstdint>
#include <iostream>
#include <vector>

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType  16
#define CONSTANT_InvokeDynamic 18
#define Large_NumericContinued 66

using namespace std;
/**classe de constantes
*/
class CONSTANT{
	public:
		/**Imprime uma constante
		*/
		void print();
};
/** Classe constante que armazena informações relacionadas a uma classe sendo uma instância da classe CONSTANT
*/
class CONSTANT_Class_info : public CONSTANT {
	public:
		u1 tag; /**< tag da classe*/
		u2 name_index; /**< indice do nome da classe*/
		/**
		* função de imprimir
		*/
		void print();
};
/** Classe constante que armazena informações relacionadas a um metodo sendo uma instância da classe CONSTANT
*/
class CONSTANT_Methodref_info : public CONSTANT {
	public:
		u1 tag; /**< tag da classe*/
		u2 class_index; /**< índice da classe*/
		u2 name_and_type_index; /**< índice do nome e tipo do método*/
		/**
		* função de imprimir
		*/
		void print();
};
/** Classe constante que armazena informações relacionadas a referência de um campo sendo uma instância da classe CONSTANT
*/
class CONSTANT_Fieldref_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u2 class_index; /**< índice da classe*/
		u2 name_and_type_index;/**< índice do nome e tipo da referência ao campo*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à referência à interface de um método sendo uma instância da classe CONSTANT
*/

class CONSTANT_InterfaceMethodref_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u2 class_index; /**< índice da classe*/
		u2 name_and_type_index;/**< índice do nome e tipo da referência relacionada a interface*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à string sendo uma instância da classe CONSTANT
*/

class CONSTANT_String_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u2 string_index; /**< índice do nome e tipo de strings*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à um inteiro sendo uma instância da classe CONSTANT
*/

class CONSTANT_Integer_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u4 bytes; /**< bytes do int*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à um ponto flutuante sendo uma instância da classe CONSTANT
*/

class CONSTANT_Float_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u4 bytes; /**< bytes do float*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à um long int sendo uma instância da classe CONSTANT
*/

class CONSTANT_Long_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u4 high_bytes; /**< bytes superiores*/
		u4 low_bytes; /**< bytes inferiores*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à um double sendo uma instância da classe CONSTANT
*/

class CONSTANT_Double_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u4 high_bytes;/**< bytes superiores*/
		u4 low_bytes;/**< bytes inferiores*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à um valor número grande sendo uma instância da classe CONSTANT
*/

class Large_Numeric_Continued_info: public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à um nome e tipo de variavel sendo uma instância da classe CONSTANT
*/

class CONSTANT_NameAndType_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u2 name_index;/**< indice do nome da classe*/
		u2 descriptor_index; /**< descritor do indice*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas ao padrão utf8 sendo uma instância da classe CONSTANT
*/

class CONSTANT_Utf8_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u2 length; /**< tamanho*/
		u1* bytes; /**< referência aos bytes de uma string*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à ao handle de métodos sendo uma instância da classe CONSTANT
*/

class CONSTANT_MethodHandle_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u1 reference_kind; /**< referência de tipo*/
		u2 reference_index; /**< referência de indice*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à ao tipo de método sendo uma instância da classe CONSTANT
*/

class CONSTANT_MethodType_info : public CONSTANT {
	public:
		u1 tag;/**< tag da classe*/
		u2 descriptor_index; /**< descritor de indices*/
		/**
		* função de imprimir
		*/
		void print();
};

/** Classe constante que armazena informações relacionadas à Invocação Dinâmica de métodos sendo uma instância da classe CONSTANT
*/

class CONSTANT_InvokeDynamic_info : public CONSTANT {
	public:
    	u1 tag;/**< tag da classe*/
    	u2 bootstrap_method_attr_index; /**< indice de atribuição de um método*/
    	u2 name_and_type_index;/**< índice do nome e tipo relacionados aos invocadores dinâmicos*/
    	/**
		* função de imprimir
		*/
    	void print();
};

/**
@union cp_info_element estrutura relacionada às informações dos elementos do constant pool
*/
union cp_info_element {
	CONSTANT_Class_info* c1; /**< referência à constante de informação da classe*/
	CONSTANT_Methodref_info* c2; /**< referência à constante de informação de métodos*/
	CONSTANT_Fieldref_info *c3; /**< referência à constante de informações de campos*/
	CONSTANT_InterfaceMethodref_info *c4; /**< referência à constante de informações de métodos*/
	CONSTANT_String_info *c5; /**< referência à constante de informações de strings*/
	CONSTANT_Integer_info *c6; /**< referência à constante de informações de inteiros*/
	CONSTANT_Float_info *c7; /**< referência à constante de informações de ponto flutuante*/
	CONSTANT_Long_info *c8; /**< referência à constante de informações de inteiros long*/
	CONSTANT_Double_info *c9; /**< referência à constante de informações de double*/
	CONSTANT_NameAndType_info *c10; /**< referência à constante de informações de nome e tipo*/
	CONSTANT_Utf8_info *c11; /**< referência à constante de informações utf8*/
	CONSTANT_MethodHandle_info *c12; /**< referência a constante de informações de handle de métodos*/
	CONSTANT_MethodType_info *c13; /**< referência a constante de informações de tipos de métodos*/
	CONSTANT_InvokeDynamic_info *c14; /**< referência a constante de informações de invocações dinâmmicas*/
	Large_Numeric_Continued_info *c15; /**< referência a constante de informações de valores numéricos grandes*/
};
/**
@struct cp_info struct que armazena informações do constant pool
*/
struct cp_info {
	u1 tag;/**< tag da classe*/
	cp_info_element constant_element; /**< elemento constante relacionado as informações do constant pool*/
};

/**
Classe que armazena e manipula informações do constant pool
*/

class Cp_info {
	public:
		vector<cp_info> constant_pool; /**< vetor de informações do constant pool*/
		/** Pega a tag referente ao constant pool
		@param tag tag do constant pool a ser pega
		@param size tamanho da tag
		@return retorna o valor pego
		*/
		u4 getConstantPoolTag(u2 tag, u4 size);
		/** Adiciona um elemento ao constant pool
		@param tag etiqueta do elemento
		@param size tamanho do elemento
		@param position posição do elemento
		@param currentSize tamanho corrente do elemento
		@param byte_array ponteiro para uma string de bytes
		*/
		void addElement(u2 tag, u4 size, u4 position, u4 currentSize, unsigned char* byte_array);
		/** Concatena Bytes
		@param buffer referência ao buffer do byte a ser concatenado
		@param size tamanho do byte
		@param referência aos bytes a serem concatenados
		*/
		void concatBytes(u1* buffer, u2 size, u1* bytes); 
		/** Pega a constantPool e armazena na estrutura
		*/
		void getConstantPool();
		/** Pega elementos relacionados a constant pool a partir de uma posição
		@param position posição
		@return retorna um valor do tipo informação do constant pool
		*/
		cp_info getCpInfoElement(u4 position);
};

#endif