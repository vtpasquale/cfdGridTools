#pragma once
#include <fstream>
using namespace std;

class Pent6
{
public:
	int n[6];
	void read(ifstream&);
	void print();
	void printVtk(FILE*);
};
