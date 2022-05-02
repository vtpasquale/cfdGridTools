#include "Tria.h"
using namespace std;
namespace GNS = GammaNamespace;

void GNS::Tria::write(FILE* fid)
{
    fprintf(fid,"%d %d %d\n", n[0], n[1], n[2]);
}

void GNS::Tria::printVtk(FILE* fid)
{
    fprintf(fid,"3 %d %d %d\n", n[0]-1, n[1]-1, n[2]-1);
}