#include "Gamma/Gamma.h"
#include "Ugr/Ugr.h"
#include <iostream>
#include <filesystem> // C++17
namespace fs = std::filesystem;

namespace UGR = UgrNamespace;


int countDistinct(int a[], int size)
{
   int i, j, count = 1;
   for (i = 1; i < size; i++){
      for (j = 0; j < i; j++){
         if (a[i] == a[j]){
            break;
         }
      }
      if (i == j){
         count++;
      }
   }
   return count;
}

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
    
    // Convert edges and count number of edge segments
    int lastEdgeType = gamma.edges[0].ref;
    int boundaryIndex = 0;    
    for (int i = 0; i < gamma.NmbEdg; i++)
    {
        // edges
        edges[i].n[0] = gamma.edges[i].n[0] - 1;
        edges[i].n[1] = gamma.edges[i].n[1] - 1;

        // count new segments (boundary face groups)
        if (gamma.edges[i].ref != lastEdgeType)
        {
            // new edge segment
            boundaryIndex++;
            lastEdgeType = gamma.edges[i].ref;
        } 
    }
    int nBoundaries = boundaryIndex + 1; 

    // Create boundaries object
    UgrNamespace::Boundary* boundaries;
    boundaries = new Boundary[nBoundaries];
    boundaries[0].edgeStartIndex = 0; 
    boundaryIndex = 0;
    lastEdgeType = gamma.edges[0].ref;
    for (int i = 0; i < gamma.NmbEdg; i++)
    {
        // new edge segment
        if (gamma.edges[i].ref != lastEdgeType)
        {
    		boundaries[boundaryIndex].type = gamma.edges[i-1].ref;
            boundaries[boundaryIndex].name = "boundary_number_"+to_string(boundaryIndex+1);
            boundaries[boundaryIndex].edgeEndIndex = i-1;
            lastEdgeType = gamma.edges[i].ref;

            boundaryIndex++;
            boundaries[boundaryIndex].edgeStartIndex = i;
        }
    }
    boundaries[boundaryIndex].type = gamma.edges[gamma.NmbEdg-1].ref;
    boundaries[boundaryIndex].name = "boundary_number_"+to_string(boundaryIndex+1);
    boundaries[boundaryIndex].edgeEndIndex = gamma.NmbEdg-1;

    // Count number of unique nodes on each edge
    int *boundaryNodes;
    int nEdgesOnBoundary;
    int uniqueNodesOnBounary[nBoundaries];
    for (int i = 0; i < nBoundaries; i++)
    {
        nEdgesOnBoundary = boundaries[i].edgeEndIndex - boundaries[i].edgeStartIndex + 1;
        boundaryNodes = new int[2*nEdgesOnBoundary];
        for (int j = 0; j < nEdgesOnBoundary; j++)
        {
            boundaryNodes[2*j] = gamma.edges[boundaries[i].edgeStartIndex+j].n[0];
            boundaryNodes[2*j+1] = gamma.edges[boundaries[i].edgeStartIndex+j].n[1];
        }
        uniqueNodesOnBounary[i] = countDistinct(boundaryNodes,2*nEdgesOnBoundary);
        printf("uniqueNodesOnBounary[%d]=%d\n",i,uniqueNodesOnBounary[i]);
    }
    delete boundaryNodes;
    
    // Determine boundary lastFace and lastNode
    int lastNode = 0;
    int lastFace = 0;
    for (int i = 0; i < nBoundaries; i++)
    {
        nEdgesOnBoundary = boundaries[i].edgeEndIndex - boundaries[i].edgeStartIndex + 1;
        if (boundaries[i].type<700 || boundaries[i].type>=800)   // NOT periodic nodes
        {
            lastNode = lastNode + uniqueNodesOnBounary[i];
            lastFace = lastFace + nEdgesOnBoundary;
        }
        else
        {
            lastNode = lastNode + nEdgesOnBoundary;
        }
        boundaries[i].lastNode = lastNode - 1;
        boundaries[i].lastFace = lastFace - 1;
    }

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