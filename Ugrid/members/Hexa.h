#pragma once
#include <fstream>
using namespace std;

class Hexa
{
public:
	int n[8];
	void read(ifstream&);
	void print();
	void printVtk(FILE*);
};

