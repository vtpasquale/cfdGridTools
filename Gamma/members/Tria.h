#pragma once
#include <stdio.h>
using namespace std;

namespace GammaNamespace{
	class Tria
	{
	public:
		int n[3];
		int ref;
 		void write(FILE*);
		void printVtk(FILE*);
	};
}