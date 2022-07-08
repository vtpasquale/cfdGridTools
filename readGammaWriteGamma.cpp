#include "Gamma/Gamma.h"
using namespace std;

int main(int argc, char* argv[]) {

    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    gamma.getMeshData();
    gamma.writeMeshData(argv[2]);


    // Define solution data
    gamma.NbrLin = gamma.NmbVer;
    gamma.SolSiz = 3;
    gamma.NbrTyp = 3;
    gamma.TypTab[0] = 1;
    gamma.TypTab[1] = 1;
    gamma.TypTab[2] = 1;

    gamma.SolTab = new double[gamma.NbrLin*gamma.SolSiz];
    for (int i = 0; i < gamma.NbrLin; i++)
    {
        gamma.SolTab[i * gamma.SolSiz + 0] = gamma.nodes[i].x;
        gamma.SolTab[i * gamma.SolSiz + 1] = gamma.nodes[i].y;
        gamma.SolTab[i * gamma.SolSiz + 2] = gamma.nodes[i].z;
    }

    // Write solution data to the file
    gamma.writeSolutionData(argv[3]);

    return 0;
}