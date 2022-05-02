#pragma once
#include <stdio.h>
using namespace std;

namespace GammaNamespace{
	class Node
	{
	public:
		double x;
		double y;
		double z;
		int rt;
		void write(FILE*);
		void printVtk(FILE*);
	};
}