#include "Plt/Plt.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    ifstream myFileStream(argv[1]);
    Plt plt;
    plt.read(myFileStream);
    plt.printVtk(argv[2]);

    return 0;
}