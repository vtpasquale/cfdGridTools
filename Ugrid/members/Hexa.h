#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{
	class Hexa
	{
	public:
		int n[8];
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}
