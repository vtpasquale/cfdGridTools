#include "Gamma/Gamma.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    gamma.getMeshData();
    gamma.printVtk(argv[2]);

    return 0;
}