#ifndef LEITOR_H
#define LEITOR_H

#include <cstdlib>
// #include <iostream>
// #include <cstdint>
#include <fstream>
#include <string>
#include <string.h>
#include "cp_info.hpp"
#include "method_info.hpp"
#include "field_info.hpp"

/** Enumerador de Sets e Gets
Possui a finalidade de criar identificadores referentes aos sets e gets do Leitor
*/
enum ReturnTypesKey{
	MAGIC_NUMBER, /**< Chave do Magic Number*/
	MINOR_VERSION, /**< Chave do Minor Version*/
	MAJOR_VERSION, /**< Chave do Major Version*/
	CONSTANT_POOL_COUNT, /**< Chave do Contador de ConstantPool*/
	CONSTANT_POOL, /**< Chave do constant pool*/
	ACCESS_FLAGS, /**< Chave das flags de acesso*/
	THIS_CLASS, /**< Chave da classe*/
	SUPER_CLASS, /**< Chave da super classe*/
	INTERFACES_COUNT, /**< Chave do Contador de Interfaces*/
	INTERFACES,  /**< Chave referente às interfaces*/
	FIELDS, /**< Chave referente aos campos*/
	FIELDS_COUNT, /**< Chave do contador de campos*/
	METHODS, /**< Chave dos métodos*/
	METHODS_COUNT, /**< Chave do contador de métodos*/
	ATTRIBUTES_COUNT, /**< Chave do contador de atributos*/
	ATTRIBUTES /**< Chave referente aos atributos*/
};
// #define u1 uint8_t
// #define u2 uint16_t
// #define u4 uint32_t
using namespace std;
/** Classe leitor responsável por fazer a leitura de dados do arquivo .class
*/
class Leitor {
	private:
		u4 magic; // OK
		u2 minor_version; //OK
		u2 major_version; //OK
		u2 constant_pool_count; //OK
		Cp_info *constant_pool; //OK-
		u2 access_flags; //OK
		u2 this_class; //OK
		u2 super_class;//OK
		u2 interfaces_count;//OK
		u2 * interfaces; // OK
		u2 fields_count; //  OK
		vector<Field_info> fields;// Faltando
		u2 methods_count; // 
		Method_info *methods; // Faltando
		u2 attributes_count; // 
		vector< Attribute_info> attributes; // Faltando

		u4 current_size;	// atributo não oficial, guarda a posicão atual de memória
		bool setMagicNumber();
		bool setMinorVersion();
		bool setMajorVersion();
		bool setConstantPoolCount();
		bool setConstantPool();
		bool setAccessFlags();
		bool setThisClass();
		bool setSuperClass();
		bool setInterfacesCount();
		bool setInterfaces();
		bool setFieldsCount();
		bool setFields();
		bool setMethodsCount();
		bool setMethods();
		bool setAttributesCount();
		Attribute_info* setAttributes(u2 attribute_name_index, u4 attribute_length);
		u2 getInterfacesCount();
		u2 getMinorVersion();
		u2 getMajorVersion();
    u2 getConstantPoolCount();
		u2 getFieldsCount();
		Cp_info * getConstantPool();
		u2 getMethodsCount();
		u2 getAttributesCount();
		u2 getAccessFlags();
		u2 getThisClass();
		u2 getSuperClass();
	public:
		unsigned char* byte_array; /**< referência ao arquivo .class*/
		/** Carregador de arquivo
		Carrega um arquivo .class recebendo uma string como parametro
		@param filename nome do arquivo ao qual será lido
		*/
		void loadFile(string filename);
		/** Exibe alguns dados do Leitor
		Imprime alguns dos dados inseridos no leitor
		*/
		void exibir();
		
		/** Insere dados no Leitor a partir do arquivo lido
		Ao ler o arquivo, o leitor insere dados na estrutura a partir desta função ao qual recebe uma chave referente ao que deve ser inserido no leitor
		@param key Chave referente ao dado que será inserido no leitor
		@return retorna verdadeiro caso o dado seja inserido corretamente ou falso caso contrário
		*/
		bool set(int key);
		/** Pega dados setados no Leitor
		Ao setar dados é possível pegar estes dados através dessa função ao qual retorna a informação do dado lido
		@return dado que se deseja pegar a informação
		*/
		u2 get(int key);
		/** Pegador de Numero Mágico
		Pega o número mágico setado no Leitor
		@return retorna o número mágico lido
		*/
		u4 getMagicNumber();
		/** Pegador de Fields
		Pega fields inseridas no Leitor
		@return retorna um vetor de informações relacionadas às fields lidas
		*/
		vector<Field_info> getFields();
		/** Pegador de métodos
		Pega métodos inseridos no Leitor
		@return retorna um vetor de informações relacionadas aos métodos lidos
		*/
		vector<Method_info> getMethods();
		/** Pegador de Interfaces
		Pega interfaces inseridas no Leitor
		@return retorna uma referência das interfaces que foram inseridas
		*/
		u2 * getInterfaces();
		/** Pegador de atributos
		Pega atributos inseridos no Leitor
		@return retorna um vetor de informações referentes aos atributos lidos
		*/
		vector<Attribute_info> getAttributes();
		
		// bool setAccessFlagCount();
		/** Imprime os dados referentes às flags de acesso
		*/
		void printAccessFlags();
		/** Imprime os dados referentes à classe
		*/
		void printThisClass();
		/** Imprime dados referentes à super classe
		*/
		void printSuperClass();
		/** Imprime os dados referentes ao contador de interfaces
		*/
		void printInterfaceCont();
		/** Imprime os dados referentes às Interfaces
		*/
		void printInterfaces();
		/**Imprime dados referentes ao contador de interfaces
		*/
		void printFieldsCount();
		/** Lê um byte do arquivo Carregado
		@return retorna 1 byte
		*/
		u1 read1byte();
		/** Lê dois bytes do arquivo Carregado
		@return retorna 2 bytes
		*/
		u2 read2byte();
		/** Lê quatro bytes do arquivo Carregado
		@return retorna 4 bytes
		*/
		u4 read4byte();
};

#endif