#include "Gamma/Gamma.h"
#include "Ugr/Ugr.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

namespace UGR = UgrNamespace;

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
    
    int lastEdgeType = gamma.edges[0].ref;
    int boundaryIndex = 0;    
    for (int i = 0; i < gamma.NmbEdg; i++)
    {
        // edges
        edges[i].n[0] = gamma.edges[i].n[0] - 1;
        edges[i].n[1] = gamma.edges[i].n[1] - 1;

        // count segments (boundary face groups)
        if (gamma.edges[i].ref != lastEdgeType)
        {
            // new edge segment
            boundaryIndex++;
            lastEdgeType = gamma.edges[i].ref;
        }
    }
    int nBoundaries = boundaryIndex + 1;

    // Boundaries object
    UgrNamespace::Boundary* boundaries;
    boundaries = new Boundary[nBoundaries];
    boundaryIndex = 0;
    lastEdgeType = gamma.edges[0].ref;
    for (int i = 0; i < gamma.NmbEdg; i++)
    {
        // new edge segment
        if (gamma.edges[i].ref != lastEdgeType)
        {
    		boundaries[boundaryIndex].type = gamma.edges[i-1].ref;
    		boundaries[boundaryIndex].lastFace = i-1;
	    	boundaries[boundaryIndex].lastNode = i-1; // I think lastFace and lastNode should be unified in the Ugr format.
            boundaries[boundaryIndex].name = "bondary_number_"+to_string(boundaryIndex+1);
            lastEdgeType = gamma.edges[i].ref;
            boundaryIndex++;
        }
    }
    boundaries[boundaryIndex].type = gamma.edges[gamma.NmbEdg-1].ref;
    boundaries[boundaryIndex].lastFace = gamma.NmbEdg-1;
	boundaries[boundaryIndex].lastNode = gamma.NmbEdg-1;
    boundaries[boundaryIndex].name = "bondary_number_"+to_string(boundaryIndex+1);

    // Store data in Ugr object and write to file
    Ugr ugr;
    ugr.nNodes = gamma.NmbVer;
    ugr.nElements = gamma.NmbTri;
    ugr.nEdges = gamma.NmbEdg;
    ugr.nBoundaries = nBoundaries;
    
    // model data
    ugr.nodes = nodes;
    ugr.trias = trias;
    ugr.edges = edges;
    ugr.boundaries = boundaries;

    ugr.write(argv[2]);

    return 0;
}