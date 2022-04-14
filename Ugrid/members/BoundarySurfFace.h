#pragma once
#include <fstream>
using namespace std;

namespace UgridNamespace{

	class BoundarySurfFace
	{
	public:
		int n;
		void read(ifstream&);
		void print();
	};
	
}