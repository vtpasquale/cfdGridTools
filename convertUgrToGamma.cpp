#include "Ugr/Ugr.h"
#include "Gamma/Gamma.h"
#include <fstream>
#include <iostream>
using namespace std;
namespace GNS = GammaNamespace;

int main(int argc, char *argv[])
{

    // Read Ugr File
    ifstream myFileStream(argv[1]);
    Ugr ugr;
    ugr.read(myFileStream);

    // Convert to Ugr data to Gamma member data
    GNS::Node nodes[ugr.nNodes];
    GNS::Tria trias[ugr.nElements];
    GNS::Edge edges[ugr.nEdges];

    for (int i = 0; i < ugr.nNodes; i++)
    {
        nodes[i].x = ugr.nodes[i].x;
        nodes[i].y = ugr.nodes[i].y;
        nodes[i].z = 0.0;
        nodes[i].rt = 99;
    }

    for (int i = 0; i < ugr.nElements; i++)
    {
        trias[i].n[0] = ugr.trias[i].n[0] + 1;
        trias[i].n[1] = ugr.trias[i].n[1] + 1;
        trias[i].n[2] = ugr.trias[i].n[2] + 1;
        trias[i].ref = 999;
    }

    for (int i = 0; i < ugr.nBoundaries; i++)
    {
        for (int j = ugr.boundaries[i].edgeStartIndex; j < ugr.boundaries[i].edgeEndIndex; j++)
        {
            edges[j].n[0] = ugr.edges[j].n[0] + 1;
            edges[j].n[1] = ugr.edges[j].n[1] + 1;
            edges[j].ref = ugr.boundaries[i].type;
        }
    }

    // Store data in Gamma object and write to file
    Gamma gamma;
    // header data
    gamma.FilVer = 3;
    gamma.dim = 2;
    gamma.NmbVer = ugr.nNodes;
    gamma.NmbTri = ugr.nElements;
    gamma.NmbEdg = ugr.nEdges;

    // model data
    gamma.nodes = nodes;
    gamma.trias = trias;
    gamma.edges = edges;

    gamma.writeMeshData(argv[2]);

    // Write boundary data to FUN3D mapbc (if three input arguments)
    if (argc > 3)
    {
        FILE *fid;
        fid = fopen(argv[3], "w");
        fprintf(fid, "%d\n", ugr.nBoundaries);
        for (int i = 0; i < ugr.nBoundaries; i++)
        {
            fprintf(fid, "%d %d %s\n", i + 1, ugr.boundaries[i].type, ugr.boundaries[i].name.c_str());
        }
        fclose(fid);
    }

    return 0;
}