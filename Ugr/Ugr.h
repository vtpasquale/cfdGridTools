#pragma once
#include "members/Node.h"
#include "members/Tria.h"
#include "members/Boundary.h"
#include "members/Edge.h"
#include "members/blazekReadline.h"
#include <fstream>
using namespace std;
using namespace UgrNamespace;

class Ugr
{
public:
    // Header data
    int nNodes;
    int nElements;
    int nBoundaries;
    int nEdges;

    // Model data
	UgrNamespace::Node* nodes;
    UgrNamespace::Tria* trias;
    UgrNamespace::Edge* edges;
    UgrNamespace::Boundary* boundaries;

    // Methods
    void read(ifstream&);
    void write(const char* myFileName);
    void printVtk(const char* myFileName);

private:
    void readHeaderData(ifstream&);
    void readModelData(ifstream&);
};