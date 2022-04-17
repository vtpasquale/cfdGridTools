#include "Plt/Plt.h"
#include "Plt/Var.h"

int main(int argc, char* argv[]) {

    // Read Plt File
    ifstream myFileStream(argv[1]);
    Plt plt;
    plt.read(myFileStream);
    plt.printVtk(argv[3]);

    // Read Solution
    Var var;
    var.read(argv[2],plt.nNodes);
    var.appendVtk(argv[3]);

    return 0;
}