#pragma once
#include "members/Node.h"
#include "members/Tria.h"
#include "members/Edge.h"
#include "members/blazekReadline.h"
#include <fstream>
using namespace std;
using namespace PltNamespace;

class Plt
{
public:
    // Header data
    int nElements;
    int nNodes;
    int nEdges;

    // Model data
	Node* nodes;
    Tria* trias;
    Edge* edges;

    // Methods
    void read(ifstream&);
    void printPlt();
    void printVtk(const char* myFileName);

private:
    void readHeaderData(ifstream&);
    void readModelData(ifstream&);
};