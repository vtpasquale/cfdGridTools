#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{
	class Pent5
	{
	public:
		int n[5];
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}