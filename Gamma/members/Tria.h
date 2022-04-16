#pragma once
#include <stdio.h>
using namespace std;

namespace GammaNamespace{
	class Tria
	{
	public:
		int n[3];
 		void print();
		void printVtk(FILE*);
	};
}