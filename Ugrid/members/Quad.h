#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{
	class Quad
	{
	public:
		int n[4];
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}
