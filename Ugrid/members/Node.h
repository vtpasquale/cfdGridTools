#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{
	class Node
	{
	public:
		double x;
		double y;
		double z;
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}