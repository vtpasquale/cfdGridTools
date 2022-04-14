#pragma once
#include <fstream>
using namespace std;

class Node
{
public:
	double x;
	double y;
	double z;
	void read(ifstream&);
	void print();
	void printVtk(FILE*);
};