#pragma once
#include <fstream>
using namespace std;

namespace UgrNamespace{
	class Node
	{
	public:
		double x;
		double y;
		void read(ifstream&);
		void write(FILE*);
		void printVtk(FILE*);
	};
}