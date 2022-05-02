#pragma warning(disable : 4996)
#include "Ugrid.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace UgridNamespace;

void Ugrid::read(ifstream& myFileStream)
{
    readHeaderData(myFileStream);
    readModelData(myFileStream);
}

void Ugrid::write(const char* myFileName)
{
    FILE* fid;
    fid = fopen(myFileName,"w");

    fprintf(fid,"%d %d %d %d %d %d %d\n", nNodes, nSurfTrias, nSurfQuads, nVolTets, nVolPents5, nVolPents6, nVolHexs);

    // Print nodes
    for (int i = 0; i < nNodes; i++)
        nodes[i].write(fid);

    // Print trias
    for (int i = 0; i < nSurfTrias; i++)
        trias[i].write(fid);
    //Print Quads
    for (int i = 0; i < nSurfQuads; i++)
        quads[i].write(fid);

    //Print Surface Bondary Face IDs
    for (int i = 0; i < nBoundarySurfFaces; i++)
        boundarySurfFaces[i].write(fid);

    //Print Tets
    for (int i = 0; i < nVolTets; i++)
        tets[i].write(fid);

    //Print Pent5
    for (int i = 0; i < nVolPents5; i++)
        pent5s[i].write(fid);

    //Print Pent6
    for (int i = 0; i < nVolPents6; i++)
        pent6s[i].write(fid);

    //Print Hex
    for (int i = 0; i < nVolHexs; i++)
        hexa[i].write(fid);
}

void Ugrid::printVtk(const char* myFileName)
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
    fprintf(fid, "CELLS %d %d\n", nElements, nCellData);
    // Print trias
    for (int i = 0; i < nSurfTrias; i++)
        trias[i].printVtk(fid);

    //Print Quads
    for (int i = 0; i < nSurfQuads; i++)
        quads[i].printVtk(fid);

    //Print Tets
    for (int i = 0; i < nVolTets; i++)
        tets[i].printVtk(fid);

    //Print Pent5
    for (int i = 0; i < nVolPents5; i++)
        pent5s[i].printVtk(fid);

    //Print Pent6
    for (int i = 0; i < nVolPents6; i++)
        pent6s[i].printVtk(fid);

    //Print Hex
    for (int i = 0; i < nVolHexs; i++)
        hexa[i].printVtk(fid);

    // CELL TYPES
    fprintf(fid, "CELL_TYPES %d\n", nElements);

    // trias
    for (int i = 0; i < nSurfTrias; i++)
        fprintf(fid, "5\n");

    // Quads
    for (int i = 0; i < nSurfQuads; i++)
        fprintf(fid, "9\n");

    // Tets
    for (int i = 0; i < nVolTets; i++)
        fprintf(fid, "10\n");

    // Pent5
    for (int i = 0; i < nVolPents5; i++)
        fprintf(fid, "14\n");

    // Pent6
    for (int i = 0; i < nVolPents6; i++)
        fprintf(fid, "13\n");

    // Hex
    for (int i = 0; i < nVolHexs; i++)
        fprintf(fid, "12\n");

    fclose(fid);

}

void Ugrid::readHeaderData(ifstream& myFileStream)
{
    string line;
    line = ReadLine(myFileStream);
    stringstream(line) >> nNodes >> nSurfTrias >> nSurfQuads >> nVolTets >> nVolPents5 >> nVolPents6 >> nVolHexs;

    nBoundarySurfFaces = nSurfTrias + nSurfQuads;
    nElements = nSurfTrias + nSurfQuads + nVolTets + nVolPents5 + nVolPents6 + nVolHexs;
    nCellData = 4 * nSurfTrias + 5 * nSurfQuads + 5 * nVolTets + 6 * nVolPents5 + 7 * nVolPents6 + 9 * nVolHexs;
}

void Ugrid::readModelData(ifstream& myFileStream)
{
    //Read Nodes
    nodes = new Node[nNodes];
    for (int i = 0; i < nNodes; i++)
        nodes[i].read(myFileStream);

    //Read Trias
    trias = new Tria[nSurfTrias];
    for (int i = 0; i < nSurfTrias; i++)
        trias[i].read(myFileStream);

    //Read Quads
    quads = new Quad[nSurfQuads];
    for (int i = 0; i < nSurfQuads; i++)
        quads[i].read(myFileStream);

    //Read Surface Bondary Face IDs
    boundarySurfFaces = new BoundarySurfFace[nBoundarySurfFaces];
    for (int i = 0; i < nBoundarySurfFaces; i++)
        boundarySurfFaces[i].read(myFileStream);

    //Read Tets
    tets = new Tet[nVolTets];
    for (int i = 0; i < nVolTets; i++)
        tets[i].read(myFileStream);

    //Read Pent5
    pent5s = new Pent5[nVolPents5];
    for (int i = 0; i < nVolPents5; i++)
        pent5s[i].read(myFileStream);

    //Read Pent6
    pent6s = new Pent6[nVolPents6];
    for (int i = 0; i < nVolPents6; i++)
        pent6s[i].read(myFileStream);

    //Read Hex
    hexa = new Hexa[nVolHexs];
    for (int i = 0; i < nVolHexs; i++)
        hexa[i].read(myFileStream);

}