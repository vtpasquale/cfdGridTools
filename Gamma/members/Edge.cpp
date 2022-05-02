#include "Edge.h"
using namespace std;
namespace GNS = GammaNamespace;

void GNS::Edge::write(FILE* fid)
{
    printf("%d %d %d\n", n[0], n[1], ref);
}