#include "Gamma/Gamma.h"
using namespace std;

int main(int argc, char* argv[]) {

    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    gamma.getMeshData();
    gamma.writeMeshData(argv[2]);

    return 0;
}