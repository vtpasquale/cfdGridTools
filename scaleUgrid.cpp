#include "Ugrid/Ugrid.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    // Read Ugrid
    ifstream myFileStream(argv[1]);
    Ugrid ugrid;
    ugrid.read(myFileStream);

    // Scale Ugrid
    double scaleFactor;
    scaleFactor=atof(argv[3]);
    printf("Scale factor = %f\n",scaleFactor);
    for (int i = 0; i < ugrid.nNodes; i++){
        ugrid.nodes[i].x = scaleFactor*ugrid.nodes[i].x;
        ugrid.nodes[i].y = scaleFactor*ugrid.nodes[i].y;
        ugrid.nodes[i].z = scaleFactor*ugrid.nodes[i].z;
    }

    // Write scaled Ugrid
    ugrid.write(argv[2]);

    return 0;
}