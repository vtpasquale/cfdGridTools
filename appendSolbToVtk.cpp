#include "Gamma/Gamma.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

//
// Appends solution data in .solb file to existing .vtk file that only contains mesh data
// The mesh .vtk data can be created using Refine
//

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
    fs::path vtk = argv[1];
    fs::path solb = argv[2];
    if (!fs::exists(solb))
    {
        std::cout << "Input solution file " << solb.filename() << " not found.\n";
        return 1;
    }
    if (solb.extension().compare(".solb") != 0 && solb.extension().compare(".sol") != 0)
    {
        std::cout << "Input solution file extension is " << solb.extension() << ". The extension should be .sol or .solb.\n";
        return 1;
    }

    if (vtk.extension().compare(".vtk") != 0)
    {
        std::cout << "Output solution file extension is " << vtk.extension() << ". The extension should be .vtk.\n";
        return 1;
    }
    if (fs::exists(vtk))
    {
        std::cout << "Solution data will be appended to " << vtk.filename() << ".\n";
    }
    else
    {
        std::cout << "Cannot find file: " << vtk.filename() << ". This process requires an existing vtk file.\n";
        return 1;
    }

    // Gamma solution file
    Gamma gamma;
    gamma.getMeshInfo(argv[2]);
    gamma.getSolutionData();

    std::cout << "gamma.NbrLin = " << gamma.NbrLin << "\n";
    std::cout << "gamma.SolSiz = " << gamma.SolSiz << "\n";
    std::cout << "gamma.NbrTyp = " << gamma.NbrTyp << "\n";

    // Append VTK file
    FILE *fid;
    fid = fopen(argv[1], "a");

    // Point data section break
    fprintf(fid,"POINT_DATA %d\n",gamma.NbrLin);

    // Write each solution to a scalar output
    int nl = gamma.NbrLin;
    int ss = gamma.SolSiz;
    for (int i = 0; i < ss; i++)
    {
        fprintf(fid,"SCALARS solution%d float\n",i+1);
        fprintf(fid,"LOOKUP_TABLE default\n");
        for (int j=0; j < nl; j++)
        {
           fprintf(fid,"%1.16E\n",gamma.SolTab[ss*j+i]);
        }
    }
    
    fclose(fid);
    return 0;
}