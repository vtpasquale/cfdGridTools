#pragma warning(disable : 4996)
#include "Plt.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace PltNamespace;

void Plt::read(ifstream& myFileStream)
{
    readHeaderData(myFileStream);
    readModelData(myFileStream);
}

void Plt::printPlt()
{
    printf("%d %d %d\n", nElements,nNodes,nEdges);

    // Print trias
    for (int i = 0; i < nElements; i++)
        trias[i].print();

    // Print nodes
    for (int i = 0; i < nNodes; i++)
        nodes[i].print();

    //Print edges
    for (int i = 0; i < nEdges; i++)
        edges[i].print();

}

void Plt::printVtk(const char* myFileName)
{
    // Write the mesh to a.vtk file.
    // https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf
    FILE* fid;
    fid = fopen(myFileName,"w");
    fprintf(fid, "# vtk DataFile Version 3.0\n");
    fprintf(fid, "My example\n");
    fprintf(fid, "ASCII\n");

    // POINTS
    fprintf(fid, "\nDATASET UNSTRUCTURED_GRID\n");
    fprintf(fid, "POINTS %d float\n", nNodes);
    for (int i = 0; i < nNodes; i++)
        nodes[i].printVtk(fid);

    // CELLS
    fprintf(fid, "CELLS %d %d\n", nElements, 4 * nElements);
    // Print trias
    for (int i = 0; i < nElements; i++)
        trias[i].printVtk(fid);

    // CELL TYPES
    fprintf(fid, "CELL_TYPES %d\n", nElements);

    // trias
    for (int i = 0; i < nElements; i++)
        fprintf(fid, "5\n");

    fclose(fid);

}

void Plt::readHeaderData(ifstream& myFileStream)
{
    string line;
    line = ReadLine(myFileStream);
    stringstream(line) >> nElements >> nNodes >> nEdges;

}

void Plt::readModelData(ifstream& myFileStream)
{

    //Read Trias
    trias = new Tria[nElements];
    for (int i = 0; i < nElements; i++)
        trias[i].read(myFileStream);

    //Read Nodes
    nodes = new Node[nNodes];
    for (int i = 0; i < nNodes; i++)
        nodes[i].read(myFileStream);

    //Read Edges
    edges = new Edge[nEdges];
    for (int i = 0; i < nEdges; i++)
        edges[i].read(myFileStream);

}