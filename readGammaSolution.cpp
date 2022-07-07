#include "Gamma/Gamma.h"
using namespace std;

int main(int argc, char* argv[]) {

    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    
    printf("_a_\n");
    gamma.getSolutionData();

    return 0;
}