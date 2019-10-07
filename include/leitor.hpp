#ifndef LEITOR_H
#define LEITOR_H

#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
using namespace std;

class Leitor {
	public:
		char* loadFile(string filename);
};

#endif