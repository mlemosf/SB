#ifndef EXIBIDOR_H
#define EXIBIDOR_H

#include <cstdlib>
// #include <iostream>
// #include <cstdint>
#include <fstream>
#include <string>
#include <string.h>
#include "cp_info.hpp"
#include "leitor.hpp"

#ifdef __WIN32
  #define CLS "cls"
#elif __linux__
  #define CLS "clear"
#endif
/** Classe do exibidor responsável por exibir os dados a partir de um leitor
*/
class Exibidor {
private:
	Leitor r;
	int show;
	void ShowField(int s);
	void ShowMethod(int s);
public:
	/** Construtor do exbidor
	recebe um leitor a ser exibido como parametro
	@param l leitor a ser exibido
	*/
	Exibidor(Leitor l);
	/** Função de mostrar
	Imprime todos os dados lidos pelo leitor
	*/
	void Mostrar();
	/** Função de informações Gerais
	Imprime todos os dados referentes às informações gerais lidas do leitor
	*/
	void GeneralInformation();
	/** Função de Constant Pool
	Imprime todos os dados referentes ao constant pool lido do leitor
	*/
	void ConstantPool();
	/** Função de Interfaces
	Imprime todos os dados referentes às interfaces lidas do leitor
	*/
	void Interfaces();
	/** Função de Fields
	Imprime todos os dados referentes aos campos lidos do leitor
	*/
	void Fields();
	/** Função de Metodos
	Imprime todos os dados referentes aos metodos lidos do leitor
	*/
	void Methods();
	/** Função de Atributos
	Imprime todos os dados referentes aos atributos lidos do leitor
	*/
	void Attributes();
};

#endif