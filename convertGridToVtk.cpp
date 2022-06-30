#include "Gamma/Gamma.h"
#include "Ugrid/Ugrid.h"
#include "Plt/Plt.h"
#include "Ugr/Ugr.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{

    // Confirm number of inputs
    std::cout << "Number of inputs: " << argc - 1 << "\n";
    if (argc != 3)
    {
        std::cout << "There should be two input arguments.\n";
        return 1;
    }

    // Print all input arguments
    for (int i = 1; i < argc; i++)
        std::cout << "argv[" << i << "] = " << argv[i] << "\n";

    // Check inputs
    fs::path inputGridFile = argv[1];
    fs::path outputGridFile = argv[2];
    if (!fs::exists(inputGridFile))
    {
        std::cout << "Input grid file " << inputGridFile.filename() << " not found.\n";
        return 1;
    }    
    if (outputGridFile.extension().compare(".vtk")!=0)
    {
        std::cout << "Output grid file extension " << outputGridFile.extension() << " not supported.\n";
        return 1;
    }
    if (fs::exists(outputGridFile))
    {
        std::cout << outputGridFile.filename() << " already exists. It will be overwritten.\n";
    }
    std::cout << "Input file extension " << inputGridFile.extension() << "\n";
    std::cout << "Output file extension " << outputGridFile.extension() << "\n";

    // Read input mesh and write to .vtk format
    if (inputGridFile.extension().compare(".meshb")==0 || inputGridFile.extension().compare(".mesh")==0 )
    {
        // Gamma format
        Gamma gammaGrid;
        gammaGrid.getMeshInfo(argv[1]);
        gammaGrid.getMeshData();
        gammaGrid.printVtk(argv[2]);
    }
    else if (inputGridFile.extension().compare(".ugrid")==0)
    {
        // AFLR3 format
        ifstream myFileStream(argv[1]);
        Ugrid ugrid;
        ugrid.read(myFileStream);
        myFileStream.close();
        ugrid.printVtk(argv[2]);
    }
    else if (inputGridFile.extension().compare(".plt")==0)
    {
        // CbsFlow format
        ifstream myFileStream(argv[1]);
        Plt pltGrid;
        pltGrid.read(myFileStream);
        myFileStream.close();
        pltGrid.printVtk(argv[2]);
    }
    else if (inputGridFile.extension().compare(".ugr")==0)
    {
        // Unstruct2D format
        ifstream myFileStream(argv[1]);
        Ugr ugrGrid;
        ugrGrid.read(myFileStream);
        myFileStream.close();
        ugrGrid.write("test.ugr");
        ugrGrid.printVtk(argv[2]);
    }
    else
    {
        std::cout << "Input grid file extension " << inputGridFile.extension() << " not supported.\n";
    }

    return 0;
}