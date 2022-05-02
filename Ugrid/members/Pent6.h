#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{
	class Pent6
	{
	public:
		int n[6];
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}