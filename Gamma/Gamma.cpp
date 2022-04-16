#include "Gamma.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace GammaNamespace;

void Gamma::printVtk(const char* myFileName)
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
    fprintf(fid, "POINTS %d float\n", NmbVer);
    for (int i = 0; i < NmbVer; i++)
        nodes[i].printVtk(fid);

    // CELLS
    fprintf(fid, "CELLS %d %d\n", NmbTri, 4*NmbTri);
    // Print trias
    for (int i = 0; i < NmbTri; i++)
        trias[i].printVtk(fid);

    // CELL TYPES
    fprintf(fid, "CELL_TYPES %d\n", NmbTri);

    // trias
    for (int i = 0; i < NmbTri; i++)
        fprintf(fid, "5\n");

    fclose(fid);

}


void Gamma::getMeshData()
{
    int64_t idx;

    /* Try to open the file and ensure its version is 1
    (single precision reals) and dimension is 2 */
    int thisVer, thisDim;
    idx = GmfOpenMesh(meshFileName, GmfRead, &thisVer, &thisDim );

    if( !idx ){
        printf("cannot open mesh/solution file %s\n", meshFileName);
        exit(1);
    }

    if( !NmbVer || !NmbTri ){
        printf("No nodes  or triangles in mesh file %s\n", meshFileName);
        exit(1);
    }

    // printf("idx,thisVer,thisDim = %ld,%d,%d\n",idx,thisVer,thisDim);
    if (thisVer != 1){
        printf("thisVer != 1\n");
        exit(1);
    }

    if (thisDim != 2){
        printf("thisDim != 2\n");
        exit(1);
    }

    nodes = new Node[NmbVer];
    trias = new Tria[NmbTri];

    GmfGotoKwd( idx, GmfVertices );
    for(i=0;i<NmbVer;i++){
        GmfGetLin( idx, GmfVertices, &nodes[i].x, &nodes[i].y, &nodes[i].rt);
        nodes[i].z = 0.0;
        // printf("nodes[i].x, nodes[i].y, nodes[i].rt = %f, %f, %d \n",nodes[i].x, nodes[i].y, nodes[i].rt );
    }

    GmfGotoKwd( idx, GmfTriangles );
    for(i=0;i<NmbTri;i++)
        GmfGetLin( idx, GmfTriangles, &trias[i].n[0], &trias[i].n[1], &trias[i].n[2], &trias[i].ref);

    GmfCloseMesh( idx );
}