#pragma once
#include <fstream>
using namespace std;

namespace UgrNamespace{

	class Boundary
	{
	public:
		int type;
		int lastFace;
		int lastNode;
		string name;

		void read(ifstream&);
		void write(FILE*);
	};
	
}