#pragma once
#include <stdio.h>
using namespace std;

namespace GammaNamespace{

	class Edge
	{
	public:
		int n[2];
		int ref;
		void write(FILE*);
	};
	
}