#pragma once
#include <fstream>
using namespace std;

class BoundarySurfFace
{
public:
	int n;
	void read(ifstream&);
	void print();
};

