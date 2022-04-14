
#include <fstream>
#include <sstream>
#include "Node.h"
#include "blazekReadline.h"
using namespace std;
namespace UGN = UgridNamespace;

void UGN::Node::read(ifstream& myFileStream)
{
    string line;
    line = UGN::ReadLine(myFileStream);
    stringstream(line) >> x >> y >> z;
}

void UGN::Node::print()
{
    printf("%f %f %f\n", x, y, z);
}

void UGN::Node::printVtk(FILE* fid)
{
    fprintf(fid,"%f %f %f\n", x, y, z);
}