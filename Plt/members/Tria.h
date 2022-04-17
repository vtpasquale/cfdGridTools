#pragma once
#include <fstream>
using namespace std;

namespace PltNamespace{
	class Tria
	{
	public:
		int id;
		int n[3];
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}