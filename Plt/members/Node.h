#pragma once
#include <fstream>
using namespace std;

namespace PltNamespace{
	class Node
	{
	public:
		int id;
		double x;
		double y;
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}