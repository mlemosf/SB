#ifndef EXIBIDOR_H
#define EXIBIDOR_H

#include <cstdlib>
// #include <iostream>
// #include <cstdint>
#include <fstream>
#include <string>
#include <string.h>
#include "cp_info.hpp"

class Exbidor {
  private:
	Leitor r;
	
	public:
		Exibidor(Leitor l);
		void GeneralInformation();
		void ConstantPool();
		void Interfaces();
		void Fields();
		void Methods();
		void Attributes();

};

#endif