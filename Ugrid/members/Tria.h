#pragma once
#include <fstream>
using namespace std;

class Tria
{
public:
	int n[3];
	void read(ifstream&);
	void print();
	void printVtk(FILE*);
};
