#pragma once
#include <fstream>
using namespace std;

namespace PltNamespace{

	class Edge
	{
	public:
		int n[2];
		int element;
		int boundary;
		void read(ifstream&);
		void print();
	};
	
}