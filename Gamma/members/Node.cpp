#include "Node.h"
using namespace std;
namespace GNS = GammaNamespace;


void GNS::Node::print()
{
    printf("%f %f %f\n", x, y, z);
}

void GNS::Node::printVtk(FILE* fid)
{
    fprintf(fid,"%f %f %f\n", x, y, z);
}