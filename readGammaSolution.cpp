#include "Gamma/Gamma.h"
using namespace std;

int main(int argc, char* argv[]) {

    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    
    gamma.getSolutionData();
    gamma.writeSolutionData(argv[2]);

    return 0;
}