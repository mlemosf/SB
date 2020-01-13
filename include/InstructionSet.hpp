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
		map<int, int> pnem;
		void PrintInstr(u1 bcode);
		void PrintParam(u1 bcode);
	public:
		InstructionSet();
		string get(int key);
		void PrintAllInstr(u1 * bcode, u4 size);
};

#endif