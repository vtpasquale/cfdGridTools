#pragma warning(disable : 4996)
#include "Var.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace PltNamespace;

void Var::read(const char* myFileName, int nNodesInput)
{
    nNodes = nNodesInput;
    // Intialize string + filestream and skip first line
    string line;
    ifstream myFileStream(myFileName);
    line = ReadLine(myFileStream);

    // read line for each node
    u1 = new double[nNodes];
    u2 = new double[nNodes];
    p = new double[nNodes];
    T = new double[nNodes];
    for (int i = 0; i < nNodes-1; i++){
        line = ReadLine(myFileStream);
        stringstream(line) >> u1[i] >> u2[i] >> p[i] >> T[i];
    }

}

void Var::appendVtk(const char* myFileName)
{
    // Write the mesh to a.vtk file.
    // https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf
    FILE* fid;
    fid = fopen(myFileName,"a");

    fprintf(fid,"POINT_DATA %d\n",nNodes);
    fprintf(fid,"SCALARS u1 float\n");
    fprintf(fid,"LOOKUP_TABLE default\n");
    for (int i = 0; i < nNodes; i++)
        fprintf(fid,"%f\n",u1[i]);

    fprintf(fid,"SCALARS u2 float\n");
    fprintf(fid,"LOOKUP_TABLE default\n");
    for (int i = 0; i < nNodes; i++)
        fprintf(fid,"%f\n",u2[i]);

    fprintf(fid,"SCALARS p float\n");
    fprintf(fid,"LOOKUP_TABLE default\n");
    for (int i = 0; i < nNodes; i++)
        fprintf(fid,"%f\n",p[i]);
    
    fprintf(fid,"SCALARS T float\n");
    fprintf(fid,"LOOKUP_TABLE default\n");
    for (int i = 0; i < nNodes; i++)
        fprintf(fid,"%f\n",T[i]);    

    fclose(fid);

}