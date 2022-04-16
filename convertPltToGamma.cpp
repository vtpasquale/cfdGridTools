#include "Plt/Plt.h"
#include "Gamma/Gamma.h"
#include <fstream>
#include <iostream>
using namespace std;
namespace GNS = GammaNamespace;


int main(int argc, char* argv[]) {

    // Read Plt File
    ifstream myFileStream(argv[1]);
    Plt plt;
    plt.read(myFileStream);

    // Convert to Gamma
    GNS::Node nodes[plt.nNodes];
    GNS::Tria trias[plt.nElements];
    GNS::Edge edges[plt.nEdges];

    for (int i = 0; i < plt.nNodes; i++){
        nodes[i].x = plt.nodes[i].x;
        nodes[i].y = plt.nodes[i].y;
        nodes[i].z = 0.0;
        nodes[i].rt = 99;
    }

    for (int i = 0; i < plt.nElements; i++){
        trias[i].n[0] = plt.trias[i].n[0];
        trias[i].n[1] = plt.trias[i].n[1];
        trias[i].n[2] = plt.trias[i].n[2];
        trias[i].ref = 999;
    }

    for (int i = 0; i < plt.nEdges; i++){
        edges[i].n[0] = plt.edges[i].n[0];
        edges[i].n[1] = plt.edges[i].n[1];
        edges[i].ref  = plt.edges[i].boundary;
    }

    Gamma gamma;
    // header data 
    gamma.FilVer = 3;
    gamma.dim = 2;
    gamma.NmbVer = plt.nNodes;
    gamma.NmbTri = plt.nElements;
    gamma.NmbEdg = plt.nEdges;

    // model data
    gamma.nodes = nodes;
    gamma.trias = trias;
    gamma.edges = edges;

    gamma.writeMeshData(argv[2]);

    return 0;
}