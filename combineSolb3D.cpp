#include "Gamma/Gamma.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

//
// Combines two .solb output files from FUN3D Flow and Adjoint solutions
// Input 1 is the .solb filename from the Flow solution. Data is [rho,u,v,w,p,turb1]
// Input 2 is the .solb filename from the Adjiont solution. Data is [turb1,labmda1,labmda2,labmda3,labmda4,labmda5,labmda6]
// Input 3 is the .solb output filename, which includes the data combined by this program.
//         The combined data is [rho,u,v,w,p,turb1,labmda1,labmda2,labmda3,labmda4,labmda5,labmda6]
// 

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
    gamma1.getSolutionData();

    gamma2.getMeshInfo(argv[2]);
    gamma2.getSolutionData();

    std::cout << "gamma1.NbrLin = " << gamma1.NbrLin << "\n";
    std::cout << "gamma1.SolSiz = " << gamma1.SolSiz << "\n";
    std::cout << "gamma1.NbrTyp = " << gamma1.NbrTyp << "\n";

    // Define solution data
    gammaOut.NbrLin = gamma1.NbrLin;
    gammaOut.SolSiz = 2*gamma1.SolSiz;
    gammaOut.NbrTyp = 2*gamma1.NbrTyp;
    if (gamma1.NbrLin != gamma2.NbrLin || gamma1.SolSiz != gamma2.SolSiz-1 || gamma1.NbrTyp != gamma2.NbrTyp-1 )
    {
        std::cout << "The two input solution files have inconsistent solution data.\n";
    }

    for (int i = 0; i < gamma1.NbrTyp; i++)
    {
        gammaOut.TypTab[i              ] = gamma1.TypTab[i];
        gammaOut.TypTab[i+gamma1.NbrTyp] = gamma1.TypTab[i];
    }

    gammaOut.SolTab = new double[gammaOut.NbrLin * gammaOut.SolSiz];
    int nl = gamma1.NbrLin;
    int iss = gamma1.SolSiz;
    int oss = gammaOut.SolSiz;
    for (int i = 0; i < nl; i++)
    {
        for (int j=0; j < iss; j++)
        {
            gammaOut.SolTab[oss*i+j    ] = gamma1.SolTab[iss*i+j];
            gammaOut.SolTab[oss*i+j+iss] = gamma2.SolTab[(iss+1)*i+j+1];
        }
    }

    // header data
    gammaOut.FilVer = 3;
    gammaOut.dim = 2;

    // Write solution data to the file
    gammaOut.writeSolutionData(argv[3]);

    return 0;
}