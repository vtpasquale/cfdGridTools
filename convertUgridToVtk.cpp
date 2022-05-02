#include "Ugrid/Ugrid.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    ifstream myFileStream(argv[1]);
    Ugrid ugrid;
    ugrid.read(myFileStream);
    ugrid.printVtk(argv[2]);

    return 0;
}