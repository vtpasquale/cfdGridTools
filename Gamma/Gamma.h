#pragma once
#include "libMeshb/libmeshb7.h"
#include "members/Node.h"
#include "members/Tria.h"
#include "members/Edge.h"
using namespace GammaNamespace;

class Gamma
{
public:
    // Mesh metadata
    int        NmbVer, dim, deg, FilVer, NmbCor, NmbRidg;
    int        NmbTet, NmbHex, NmbPri, NmbPyr, NmbTri, NmbQua, NmbEdg;
    int        NmbTetP2, NmbHexQ2, NmbPriP2, NmbPyrP2, NmbTriP2, NmbQuaQ2, NmbEdgP2, NmbNod;
    int        NmbTetP3, NmbHexQ3, NmbPriP3, NmbPyrP3, NmbTriP3, NmbQuaQ3, NmbEdgP3;
    int        NmbTetP4, NmbHexQ4, NmbPriP4, NmbPyrP4, NmbTriP4, NmbQuaQ4, NmbEdgP4;
    int        OrdTet, OrdHex, OrdPri, OrdPyr, OrdTri, OrdQua, OrdEdg;
    int        OrdTetP2, OrdHexQ2, OrdPriP2, OrdPyrP2, OrdTriP2, OrdQuaQ2, OrdEdgP2;
    int        OrdTetP3, OrdHexQ3, OrdPriP3, OrdPyrP3, OrdTriP3, OrdQuaQ3, OrdEdgP3;
    int        OrdTetP4, OrdHexQ4, OrdPriP4, OrdPyrP4, OrdTriP4, OrdQuaQ4, OrdEdgP4;
    int64_t    InpMsh = 0, InpSol = 0;
    int        i, j, ite = 0;
    float      flt;
    double     dbl, time = 0.0;
    int        NbrLin, SolSiz, NbrTyp, TypTab[ GmfMaxTyp ];

    const char* meshFileName;
    double *SolTab; // Solution table

    // Mesh physical data
	GammaNamespace::Node* nodes;
    GammaNamespace::Tria* trias;
    GammaNamespace::Edge* edges;

    // Methods
    void getMeshInfo(const char* fileName);
    void getMeshData();
    void getSolutionData();
    void writeMeshData(const char* outFileName);
    void writeSolutionData(const char* outFileName);
    void printVtk(const char* myFileName);

};
