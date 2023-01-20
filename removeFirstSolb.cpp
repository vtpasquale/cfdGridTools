#include "Gamma/Gamma.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

//
// Writes a new solution file with the first solution removed
// For example, [turb1,labmda1,labmda2,labmda3,labmda4,labmda5,labmda6]
// is read and [labmda1,labmda2,labmda3,labmda4,labmda5,labmda6] is written
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
    fs::path solb1 = argv[1];
    fs::path solbOut = argv[2];
    if (!fs::exists(solb1))
    {
        std::cout << "Input solution file " << solb1.filename() << " not found.\n";
        return 1;
    }
    if (solb1.extension().compare(".solb") != 0 && solb1.extension().compare(".sol") != 0)
    {
        std::cout << "Input solution file extension is " << solb1.extension() << ". The extension should be .sol or .solb.\n";
        return 1;
    }

    if (solbOut.extension().compare(".solb") != 0 && solbOut.extension().compare(".sol") != 0)
    {
        std::cout << "Output solution file extension is " << solbOut.extension() << ". The extension should be .sol or .solb.\n";
        return 1;
    }
    if (fs::exists(solbOut))
    {
        std::cout << solbOut.filename() << " already exists. It will be overwritten.\n";
    }

    Gamma gamma1, gammaOut;
    gamma1.getMeshInfo(argv[1]);
    gamma1.getSolutionData();

    std::cout << "gamma1.NbrLin = " << gamma1.NbrLin << "\n";
    std::cout << "gamma1.SolSiz = " << gamma1.SolSiz << "\n";
    std::cout << "gamma1.NbrTyp = " << gamma1.NbrTyp << "\n";

    // Define solution data
    gammaOut.NbrLin = gamma1.NbrLin;
    gammaOut.SolSiz = gamma1.SolSiz - 1;
    gammaOut.NbrTyp = gamma1.NbrTyp - 1;

    for (int i = 0; i < gammaOut.NbrTyp; i++)
    {
        gammaOut.TypTab[i] = gamma1.TypTab[i + 1];
    }

    gammaOut.SolTab = new double[gammaOut.NbrLin * gammaOut.SolSiz];
    int nl = gamma1.NbrLin;
    int iss = gamma1.SolSiz;
    int oss = gammaOut.SolSiz;
    for (int i = 0; i < nl; i++)
    {
        for (int j=0; j < oss; j++)
        {
            gammaOut.SolTab[oss*i+j] = gamma1.SolTab[iss*i+j+1];
        }
    }

    // header data
    gammaOut.FilVer = 3;
    gammaOut.dim = 3;

    // Write solution data to the file
    gammaOut.writeSolutionData(argv[2]);

    return 0;
}