#include "Gamma/Gamma.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{

    // Confirm number of inputs
    std::cout << "Number of inputs: " << argc - 1 << "\n";
    if (argc != 4)
    {
        std::cout << "There should be three input arguments.\n";
        return 1;
    }

    // Print all input arguments
    for (int i = 1; i < argc; i++)
        std::cout << "argv[" << i << "] = " << argv[i] << "\n";

    // Check inputs
    fs::path solb1 = argv[1];
    fs::path solb2 = argv[2];
    fs::path solbOut = argv[3];
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

    if (!fs::exists(solb2))
    {
        std::cout << "Input solution file " << solb2.filename() << " not found.\n";
        return 1;
    }
    if (solb2.extension().compare(".solb") != 0 && solb2.extension().compare(".sol") != 0)
    {
        std::cout << "Input solution file extension is " << solb2.extension() << ". The extension should be .sol or .solb.\n";
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

    Gamma gamma1, gamma2, gammaOut;
    gamma1.getMeshInfo(argv[1]);
    gamma1.getMeshData();

    gamma2.getMeshInfo(argv[2]);
    gamma2.getMeshData();

    // Define solution data
    gammaOut.NbrLin = 2*gamma1.NbrLin;
    gammaOut.SolSiz = gamma1.SolSiz;
    gammaOut.NbrTyp = gamma1.NbrTyp;
    if (gamma1.NbrLin != gamma2.NbrLin || gamma1.SolSiz != gamma2.SolSiz || gamma1.NbrTyp != gamma2.NbrTyp)
    {
        std::cout << "The two input solution files have inconsistent solution data.\n";
    }

    for (int i = 0; i < gamma1.NbrTyp; i++)
    {
        gammaOut.TypTab[i] = gamma1.TypTab[i];
        if (gamma1.TypTab[i] != gamma2.TypTab[i])
        {
            std::cout << "The two input solution files have inconsistent solution types.\n";
        }
    }

    gammaOut.SolTab = new double[gammaOut.NbrLin * gammaOut.SolSiz];
    int ns = gamma1.NbrLin*gamma1.SolSiz;
    for (int i = 0; i < ns; i++)
    {
        gammaOut.SolTab[i] = gamma1.SolTab[i];
    }
    for (int i = 0; i < ns; i++)
    {
        gammaOut.SolTab[i+ns] = gamma2.SolTab[i];
    }

    // Write solution data to the file
    gammaOut.writeSolutionData(argv[3]);

    return 0;
}