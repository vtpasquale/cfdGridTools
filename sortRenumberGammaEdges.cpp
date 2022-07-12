#include "Gamma/Gamma.h"
#include "Ugrid/Mapbc.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

int countDistinct(int a[], int size)
{
    int i, j, count = 1;
    for (i = 1; i < size; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (a[i] == a[j])
            {
                break;
            }
        }
        if (i == j)
        {
            count++;
        }
    }
    return count;
}

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
    fs::path inputGridFile = argv[1];
    fs::path outputGridFile = argv[2];
    fs::path mapbcFile = argv[3];
    if (!fs::exists(inputGridFile))
    {
        std::cout << "Input grid file " << inputGridFile.filename() << " not found.\n";
        return 1;
    }
    if (inputGridFile.extension().compare(".meshb") != 0 && inputGridFile.extension().compare(".mesh") != 0)
    {
        std::cout << "Input grid file extension is " << inputGridFile.extension() << ". The extension should be .mesh or .meshb.\n";
        return 1;
    }

    if (outputGridFile.extension().compare(".meshb") != 0 && outputGridFile.extension().compare(".mesh") != 0)
    {
        std::cout << "Output grid file extension is " << outputGridFile.extension() << ". The extension should be .mesh or .meshb.\n";
        return 1;
    }
    if (fs::exists(outputGridFile))
    {
        std::cout << outputGridFile.filename() << " already exists. It will be overwritten.\n";
    }

    if (mapbcFile.extension().compare(".mapbc") != 0)
    {
        std::cout << "Mapbc file extension is " << mapbcFile.extension() << ". The extension should be .mapbc\n";
        return 1;
    }
    if (fs::exists(mapbcFile))
    {
        std::cout << "Input Mapbc file " << mapbcFile.filename() << " not found.\n";
    }

    // Read Input Gamma mesh
    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    gamma.getMeshData();

    // Read Input Mapbc file
    UgridNamespace::Mapbc mapbc;
    mapbc.read(argv[3]);
    // mapbc.write("test.mapbc");

    // Check Mapbc file has sequential indicies starting from 1.
    for (int i = 0; i < mapbc.nBoundaries; i++)
    {
        if (mapbc.boundary[i].index != i+1 )
        {
            std::cout << "This process was created for Mapbc files that have sequential indicies starting from 1. Process aborted.\n";
            return 1;
        }
    }

    for (int i = 0; i < gamma.NmbEdg; i++)
    {
        if ( gamma.edges[i].ref < 1 || gamma.edges[i].ref > mapbc.nBoundaries)
        {
            std::cout << "An edge reference is outside of the range of values specified in the Mapbc file. Process aborting.\n";
            return 1;
        }
        gamma.edges[i].ref = mapbc.boundary[gamma.edges[i].ref-1].condition;
    }
    
    // write modifed mesh to file
    gamma.writeMeshData(argv[2]);

    return 0;
}