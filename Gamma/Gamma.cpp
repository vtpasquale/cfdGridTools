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

    printf("getMeshData Check 1\n");
    int64_t idx;

    /* Try to open the file and ensure its version is 1
    (single precision reals) and dimension is 3 */

    idx = GmfOpenMesh(meshFileName, GmfRead, &FilVer, &dim );

    printf("getMeshData Check 2\n");

    if( !idx ){
        printf("cannot open mesh/solution file %s\n", meshFileName);
        exit(1);
    }

    /* Read the number of vertices and triangles and allocate
    a triangle table (tt[nbt][4]) to store each triangle
    vertices and reference (hence the fourth integer).
    Two tables are allocated for the vertices:
    ct[nbv][3] to store the three coordinates
    rt[nbv] to store the references. */

    if( !NmbVer || !NmbTri ){
        printf("No nodes  or triangles in mesh file %s\n", meshFileName);
        exit(1);
    }

    printf("getMeshData Check 3\n");

    /* Move the file pointer to the begining of vertices data
    and start to loop over them. Then do likewise with triangles. */
    double x, y, z;
    int rt;
    GmfGotoKwd( idx, GmfVertices );
    for(int i=0;i<NmbVer;i++){
        GmfGetLin( idx, GmfVertices,&x, &y, &z, &rt);
        nodes[i].x=x;
        nodes[i].y=y;
        nodes[i].z=z;
        nodes[i].rt=rt;
    }

    GmfGotoKwd( idx, GmfTriangles );

    for(int i=0;i<NmbTri;i++)
        GmfGetLin( idx, GmfTriangles, &trias[i].n[0], &trias[i].n[1], &trias[i].n[2], &trias[i].n[4] );

    GmfCloseMesh( idx );
}