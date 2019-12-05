#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#define u1 uint8_t
#define u2 uint16_t
#define u4 uint32_t

#include <cstdlib>
#include <string.h>
#include <map>
#include <iostream>
#include <stdio.h>

using namespace std;

class InstructionSet{
	private:
		map<int, string> mnem;
		void PrintInstr(u4 bcode);
	public:
		InstructionSet();
		string get(int key);
		void PrintAllInstr(u1 * bcode, u4 size);
};

#endif