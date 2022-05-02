#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{
	class Tria
	{
	public:
		int n[3];
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}