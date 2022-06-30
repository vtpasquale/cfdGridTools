#pragma once
#include <fstream>
using namespace std;

namespace UgrNamespace{

	class Edge
	{
	public:
		int n[2];
		void read(ifstream&);
		void write(FILE*);
	};
	
}