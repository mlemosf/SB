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

enum TypeShow
{
	PUBLIC,
	PRIVATE,
	PROTECTED,
	STATIC,
	FINAL,
	VOLATILE,
	TRANSIENT,
	SYNTHETIC,
	ENUM,
	SYNCHRONIZED,
	NATIVE,
	ABSTRACT,
	STRICT,
	BRIDGE,
	VARARGS,
	ALL
};

class Exibidor {
  private:
	Leitor r;
	int show;
	void ShowField(int s);
	void ShowMethod(int s);
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