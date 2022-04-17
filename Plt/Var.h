#pragma once
#include "members/blazekReadline.h"
using namespace std;
using namespace PltNamespace;

class Var
{
public:
    // meta data
    int nNodes;

    // Solution data
    double* u1;
    double* u2;
    double* p;
    double* T;

    // Methods
    void read(const char* myFileName, int nNodesInput);
    // void write(const char* myFileName);
    void appendVtk(const char* myFileName);

};