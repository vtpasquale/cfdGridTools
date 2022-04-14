#include "Edge.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace PLTN = PltNamespace;

void PLTN::Edge::read(ifstream& myFileStream)
{
    string line;
    line = PLTN::ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> element >> boundary;
}

void PLTN::Edge::print()
{
    printf("%d %d %d %d\n", n[0], n[1], element, boundary);
}