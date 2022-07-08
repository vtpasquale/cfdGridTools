#include "Gamma.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace GammaNamespace;

void Gamma::printVtk(const char *myFileName)
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
    fprintf(fid, "POINTS %d float\n", NmbVer);
    for (int i = 0; i < NmbVer; i++)
        nodes[i].printVtk(fid);

    // CELLS
    fprintf(fid, "CELLS %d %d\n", NmbTri, 4 * NmbTri);
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

    /* Try to open the file and ensure its version is 3
    (double precision reals) and dimension is 2 */
    int thisVer, thisDim;
    idx = GmfOpenMesh(meshFileName, GmfRead, &thisVer, &thisDim);

    if (!idx)
    {
        printf("Cannot open mesh/solution file %s\n", meshFileName);
        exit(1);
    }

    if (!NmbVer || !NmbTri)
    {
        printf("No nodes or triangles in mesh file %s\n", meshFileName);
        exit(1);
    }

    if (!(thisVer == 2 || thisVer == 3))
    {
        printf("Import stopped. Mesh version should be 2 or 3 (32-bit intergers and 64-bit reals). Actual Mesh version = %d. Use transmesh to convert to ascii and manual update the version number.\n", thisVer);
        exit(1);
    }

    if (thisDim != 2)
    {
        printf("thisDim != 2\n");
        exit(1);
    }

    nodes = new Node[NmbVer];
    trias = new Tria[NmbTri];
    edges = new Edge[NmbEdg];

    GmfGotoKwd(idx, GmfVertices);
    for (i = 0; i < NmbVer; i++)
    {
        GmfGetLin(idx, GmfVertices, &nodes[i].x, &nodes[i].y, &nodes[i].rt);
        nodes[i].z = 0.0;
        // printf("nodes[i].x, nodes[i].y, nodes[i].rt = %f, %f, %d \n",nodes[i].x, nodes[i].y, nodes[i].rt );
    }

    GmfGotoKwd(idx, GmfTriangles);
    for (i = 0; i < NmbTri; i++)
        GmfGetLin(idx, GmfTriangles, &trias[i].n[0], &trias[i].n[1], &trias[i].n[2], &trias[i].ref);

    GmfGotoKwd(idx, GmfEdges);
    for (i = 0; i < NmbEdg; i++)
        GmfGetLin(idx, GmfEdges, &edges[i].n[0], &edges[i].n[1], &edges[i].ref);

    GmfCloseMesh(idx);
}

void Gamma::getSolutionData()
{
    int64_t idx;

    /* Try to open the file and ensure its version is 3
    (double precision reals) and dimension is 2 */
    int thisVer, thisDim;
    idx = GmfOpenMesh(meshFileName, GmfRead, &thisVer, &thisDim);

    if (!idx)
    {
        printf("Cannot open mesh/solution file %s\n", meshFileName);
        exit(1);
    }

    if (!(thisVer == 2 || thisVer == 3))
    {
        printf("Import stopped. Mesh version should be 2 or 3 (32-bit intergers and 64-bit reals). Actual Mesh version = %d. Use transmesh to convert to ascii and manual update the version number.\n", thisVer);
        GmfCloseMesh(idx);
        exit(1);
    }

    NbrLin = GmfStatKwd(idx, GmfSolAtVertices, &NbrTyp, &SolSiz, TypTab);
    printf("NbrLin = %d, NmbTyp = %d, SolSiz = %d\n", NbrLin, NbrTyp, SolSiz);
    SolTab = new double[NbrLin*SolSiz];

    // Solution field block reading
    GmfGetBlock(idx, GmfSolAtVertices, 1, NbrLin, 0, NULL, NULL,
                GmfDoubleVec, SolSiz, &SolTab[0], &SolTab[(NbrLin*SolSiz)-1]);

    // Print each solutions of each vertices
    // for (i = 0; i < NbrLin; i++)
    // {
    //     printf("%f %f %f %f\n", SolTab[i * SolSiz + 0], SolTab[i * SolSiz + 1], SolTab[i * SolSiz + 2], SolTab[i * SolSiz + 3]);
    // }

    // Close the mesh file
    GmfCloseMesh(idx);
}

void Gamma::writeMeshData(const char *outFileName)
{
    int64_t OutMsh;
    OutMsh = GmfOpenMesh(outFileName, GmfWrite, FilVer, dim);
    if (!OutMsh)
    {
        printf("Issue accessing %s for writing output\n", outFileName);
        exit(1);
    }

    GmfSetKwd(OutMsh, GmfVertices, NmbVer);
    for (i = 0; i < NmbVer; i++)
        GmfSetLin(OutMsh, GmfVertices, nodes[i].x, nodes[i].y, nodes[i].rt);

    GmfSetKwd(OutMsh, GmfTriangles, NmbTri);
    for (i = 0; i < NmbTri; i++)
        GmfSetLin(OutMsh, GmfTriangles, trias[i].n[0], trias[i].n[1], trias[i].n[2], trias[i].ref);

    GmfSetKwd(OutMsh, GmfEdges, NmbEdg);
    for (i = 0; i < NmbEdg; i++)
        GmfSetLin(OutMsh, GmfEdges, edges[i].n[0], edges[i].n[1], edges[i].ref);

    GmfCloseMesh(OutMsh);
}

void Gamma::writeSolutionData(const char *outFileName)
{
    int64_t OutMsh;
    OutMsh = GmfOpenMesh(outFileName, GmfWrite, FilVer, dim);
    if (!OutMsh)
    {
        printf("Issue accessing %s for writing output\n", outFileName);
        exit(1);
    }

    GmfSetKwd(OutMsh, GmfSolAtVertices, NbrLin, NbrTyp, &TypTab);
    GmfSetBlock(OutMsh, GmfSolAtVertices, 1, NbrLin, 0, NULL, NULL,
         GmfDoubleVec, SolSiz, &SolTab[0], &SolTab[(NbrLin*SolSiz)-1]);

    GmfCloseMesh(OutMsh);
}