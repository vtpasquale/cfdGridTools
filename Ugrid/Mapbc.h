#pragma once
#include "members/blazekReadline.h"
using namespace std;

namespace UgridNamespace{

	class MapbcBoundary
	{
	public:
		int index;
        int condition;
        string name;
	};

	class Mapbc
	{
	public:
        int nBoundaries;
		MapbcBoundary * boundary;

		void read(const char* );
		void write(const char* );
	};
}