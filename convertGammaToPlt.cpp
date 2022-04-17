#include "Plt/Plt.h"
#include "Gamma/Gamma.h"
#include <fstream>
#include <iostream>
using namespace std;
namespace PLTN = PltNamespace;


int main(int argc, char* argv[]) {

    // Read Gamma File
    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    gamma.getMeshData();

    // Convert to Plt
    PLTN::Node nodes[gamma.NmbVer];
    PLTN::Tria trias[gamma.NmbTri];
    PLTN::Edge edges[gamma.NmbEdg];

    for (int i = 0; i < gamma.NmbVer; i++){
        nodes[i].x = gamma.nodes[i].x;
        nodes[i].y = gamma.nodes[i].y;
        nodes[i].id = i + 1;
    }

    for (int i = 0; i < gamma.NmbTri; i++){
        trias[i].n[0] = gamma.trias[i].n[0];
        trias[i].n[1] = gamma.trias[i].n[1];
        trias[i].n[2] = gamma.trias[i].n[2];
        trias[i].id = i + 1;
    }

    for (int i = 0; i < gamma.NmbEdg; i++){
        edges[i].n[0] = gamma.edges[i].n[0];
        edges[i].n[1] = gamma.edges[i].n[1];
        edges[i].boundary = gamma.edges[i].ref;
        edges[i].element = 9999; // would need to process to get correct value - the value is unused, so a dummy value is provided.
    }

    Plt plt;
    // header data 
    plt.nNodes = gamma.NmbVer;
    plt.nElements = gamma.NmbTri;
    plt.nEdges = gamma.NmbEdg;

    // model data
    plt.nodes = nodes;
    plt.trias = trias;
    plt.edges = edges;

    plt.write(argv[2]);

    return 0;
}