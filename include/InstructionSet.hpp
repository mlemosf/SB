#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include "Leitor.hpp"
#include <cstdlib>
#include <string.h>
#include <map>
#include <iostream>

class InstructionSet{
	private:
		map<int, string> mnem;
	public:
		InstructionSet();
		string get(int key);
};

#endif