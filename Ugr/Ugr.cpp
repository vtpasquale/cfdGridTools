#pragma warning(disable : 4996)
#include "Ugr.h"
#include "members/blazekReadline.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace UgrNamespace;

void Ugr::read(ifstream &myFileStream)
{
    readHeaderData(myFileStream);
    readModelData(myFileStream);
}

void Ugr::write(const char *myFileName)
{

    FILE *fid;
    fid = fopen(myFileName, "w");

    // Header
    fprintf(fid,"#\n");
    fprintf(fid,"#\n");
    fprintf(fid,"# no. of nodes, cells, boundaries:\n");
    fprintf(fid, "%d %d %d\n", nNodes, nElements, nBoundaries);

    // Boundaries
    fprintf(fid, "# boundaries: type, last face, last node, name:\n");
    for (int i = 0; i < nBoundaries; i++)
        boundaries[i].write(fid);

    // Edges
    fprintf(fid, "# boundary faces / periodic nodes (node1, node2):\n");
    for (int i = 0; i < nEdges; i++)
        edges[i].write(fid);

    // Nodes
    fprintf(fid, "# coordinates (x,y):\n");
    for (int i = 0; i < nNodes; i++)
        nodes[i].write(fid);

    // Trias
    fprintf(fid, "# triangles (node1, node2, node3):\n");
    for (int i = 0; i < nElements; i++)
        trias[i].write(fid);

    fclose(fid);
}

void Ugr::printVtk(const char *myFileName)
{
    // Write the mesh to a.vtk file.
    // https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf
    FILE *fid;
    fid = fopen(myFileName, "w");
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

void Ugr::readHeaderData(ifstream &myFileStream)
{
    string line;

    // Skip comment lines
    line = ReadLine(myFileStream);
    line = ReadLine(myFileStream);
    line = ReadLine(myFileStream);

    line = ReadLine(myFileStream);
    stringstream(line) >> nNodes >> nElements >> nBoundaries;
}

void Ugr::readModelData(ifstream &myFileStream)
{
    string commentLine;

    // Read Boundaries
    commentLine = ReadLine(myFileStream);
    boundaries = new Boundary[nBoundaries];
    for (int i = 0; i < nBoundaries; i++)
        boundaries[i].read(myFileStream);

    nEdges = boundaries[nBoundaries - 1].lastFace + 1;

    // Read Edges
    commentLine = ReadLine(myFileStream);
    edges = new Edge[nEdges];
    for (int i = 0; i < nEdges; i++)
        edges[i].read(myFileStream);

    // Read Nodes
    commentLine = ReadLine(myFileStream);
    nodes = new Node[nNodes];
    for (int i = 0; i < nNodes; i++)
        nodes[i].read(myFileStream);

    // Read Trias
    commentLine = ReadLine(myFileStream);
    trias = new Tria[nElements];
    for (int i = 0; i < nElements; i++)
        trias[i].read(myFileStream);
}