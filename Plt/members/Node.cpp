
#include <fstream>
#include <sstream>
#include "Node.h"
#include "blazekReadline.h"
using namespace std;
namespace PLTN = PltNamespace;

void PLTN::Node::read(ifstream& myFileStream)
{
    string line;
    line = PLTN::ReadLine(myFileStream);
    stringstream(line) >> id >> x >> y;
}

void PLTN::Node::print()
{
    printf("%d %f %f 0.0\n", id, x, y);
}

void PLTN::Node::printVtk(FILE* fid)
{
    fprintf(fid,"%f %f 0.0\n", x, y);
}