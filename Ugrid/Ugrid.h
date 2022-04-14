#pragma once
#include "members/Node.h"
#include "members/Tria.h"
#include "members/Quad.h"
#include "members/BoundarySurfFace.h"
#include "members/Tet.h"
#include "members/Pent5.h"
#include "members/Pent6.h"
#include "members/Hexa.h"
#include "members/blazekReadline.h"
#include <fstream>
using namespace std;
using namespace UgridNamespace;

class Ugrid
{
public:
    // Header data
    int nNodes;
    int nSurfTrias;
    int nSurfQuads;
    int nVolTets;
    int nVolPents5;
    int nVolPents6;
    int nVolHexs;

    // Derived from header data
    int nBoundarySurfFaces;
    int nElements;
    int nCellData;

    // Model data
	Node* nodes;
    Tria* trias;
    Quad* quads;
    BoundarySurfFace* boundarySurfFaces;
    Tet* tets;
    Pent5* pent5s;
    Pent6* pent6s;
    Hexa* hexa;

    // Methods
    void read(ifstream&);
    void printUgrid();
    void printVtk(const char* myFileName);

private:
    void readHeaderData(ifstream&);
    void readModelData(ifstream&);
};

