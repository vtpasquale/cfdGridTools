#pragma once
#include <stdio.h>
using namespace std;

namespace GammaNamespace{
	class Node
	{
	public:
		float x;
		float y;
		float z;
		int rt;
		void print();
		void printVtk(FILE*);
	};
}