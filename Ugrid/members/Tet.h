#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{
	class Tet
	{
	public:
		int n[4];
		void read(ifstream&);
		void print();
		void printVtk(FILE*);
	};
}
