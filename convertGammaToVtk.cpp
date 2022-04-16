#include "Gamma/Gamma.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    printf("Check 0\n");

    Gamma gamma;
    gamma.getMeshInfo(argv[1]);

    printf("Check 1\n");

    gamma.getMeshData();

    printf("Check 2\n");

    gamma.printVtk("gamma.vtk");
    // gamma.printVtk(argv[2]);

    printf("Check 3\n");


    return 0;
}