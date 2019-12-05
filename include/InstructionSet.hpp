#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

#include <cstdlib>
#include <string.h>
#include <map>
#include <iostream>

using namespace std;

class InstructionSet{
	private:
		map<int, string> mnem;
	public:
		InstructionSet();
		string get(int key);
		void PrintInstr(u1 bcode);
};

#endif