#pragma once
#include <fstream>
using namespace std;

class Pent5
{
public:
	int n[5];
	void read(ifstream&);
	void print();
	void printVtk(FILE*);
};
