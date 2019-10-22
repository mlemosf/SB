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

class Exibidor {
  private:
	Leitor r;
	public:
		Exibidor(Leitor l);
		void Mostrar();
		void GeneralInformation();
		void ConstantPool();
		void Interfaces();
		void Fields();
		void Methods();
		void Attributes();
};

#endif