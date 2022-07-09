#include "Gamma/Gamma.h"
#include "Ugr/Ugr.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

namespace UGR = UgrNamespace;

// The Ugr format (for the Blazek Unstruct2D code) is restrictive in the following ways:
// [1] The boundaries are arranged into segments (face groups - this is typical)
// [2] Each node can only be in a one boundary segment
// [3] The boundary nodes must be defined first in the file. 
//     The nodes for the first segment must be defined first, 
//     followed by the nodes for the second segement, and so on.
//
// This format coverter renumbers the nodes to comply with the format rules

// Boundary condition type must be between 100 and 799

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
    if (inputGridFile.extension().compare(".meshb")!=0 && inputGridFile.extension().compare(".mesh")!=0 )
    {
        std::cout << "Input grid file extension is " << inputGridFile.extension() << ". The extension should be .mesh or .meshb.\n";
        return 1;
    }
    if (outputGridFile.extension().compare(".ugr")!=0)
    {
        std::cout << "Output grid file extension is " << outputGridFile.extension() << ". The extension should be .ugr.\n";
        return 1;
    }
    if (fs::exists(outputGridFile))
    {
        std::cout << outputGridFile.filename() << " already exists. It will be overwritten.\n";
    }
    std::cout << "Input file extension " << inputGridFile.extension() << "\n";
    std::cout << "Output file extension " << outputGridFile.extension() << "\n";

    // Read Gamma mesh
    Gamma gamma;
    gamma.getMeshInfo(argv[1]);
    gamma.getMeshData();

    // Convert to Ugr member data
    UGR::Node nodes[gamma.NmbVer];
    UGR::Tria trias[gamma.NmbTri];
    UGR::Edge edges[gamma.NmbEdg];

    for (int i = 0; i < gamma.NmbVer; i++)
    {
        nodes[i].x = gamma.nodes[i].x;
        nodes[i].y = gamma.nodes[i].y;
    }

    for (int i = 0; i < gamma.NmbTri; i++)
    {
        trias[i].n[0] = gamma.trias[i].n[0] - 1;
        trias[i].n[1] = gamma.trias[i].n[1] - 1;
        trias[i].n[2] = gamma.trias[i].n[2] - 1;
    }

    for (int i = 0; i < gamma.NmbEdg; i++)
    {
        edges[i].n[0] = gamma.edges[i].n[0] - 1;
        edges[i].n[1] = gamma.edges[i].n[1] - 1;
        // edges[i].ref = boundaryIndex;
    }

    // Loop over all possible boundary IDs and set a flag to true if used
    bool typeUsedFlag[800];
    for (int i = 0; i < gamma.NmbEdg; i++)
    {
        if (gamma.edges[i].ref < 100 || gamma.edges[i].ref > 799 )
        {
            std::cout << "Boundary reference number must be between 100 and 799. Value is " << gamma.edges[i].ref << ".\n";
            return 1;
        }
        typeUsedFlag[gamma.edges[i].ref]=true;
    }   

    // Initialize renumbering data
    int nextNode = 0;
    int newNodeNumbers[gamma.NmbVer];
    for (int i = 0; i < gamma.NmbVer; i++)
    {
        newNodeNumbers[i] = -777;
    }

    // Loop over all boundary IDs. Count segments. Set renumbering node IDs
    int nBoundarySegments = 0;
    for (int i = 100; i < 800; i++)
    {
        if (typeUsedFlag[i]==true)
        {
            nBoundarySegments++;
            for (int j = 0; j < gamma.NmbEdg; j++)
            {
                if (i==gamma.edges[j].ref)
                {
                    // TODO add logic to not renumber more than once
                    newNodeNumbers[gamma.edges[j].n[1]] = nextNode;
                    nextNode++;
                    newNodeNumbers[gamma.edges[j].n[2]] = nextNode;
                    nextNode++;
                }
            }
        }
    }

    // Finish defining new node IDs by looping over remaining nodes
    for (int i = 0; i < gamma.NmbVer; i++)
    {
        if (newNodeNumbers[i]==-777)
        {
            newNodeNumbers[i] = nextNode;
            nextNode++;
        }
    }

    // Check the total
    if (nextNode != gamma.NmbVer)
    {
        std::cout << "Boundary processing error!\n";
        return 1;
    }

    // TODO Renumber the member data

    // Store data in Ugr object and write to file
    Ugr ugr;
    ugr.nNodes = gamma.NmbVer;
    ugr.nElements = gamma.NmbTri;
    ugr.nEdges = gamma.NmbEdg;

    // model data
    ugr.nodes = nodes;
    ugr.trias = trias;
    ugr.edges = edges;

    ugr.write(argv[2]);

    return 0;
}