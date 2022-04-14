
#include <fstream>
#include <sstream>
#include "Node.h"
#include "blazekReadline.h"
using namespace std;

void Node::read(ifstream& myFileStream)
{
    string line;
    line = ReadLine(myFileStream);
    stringstream(line) >> x >> y >> z;
}

void Node::print()
{
    printf("%f %f %f\n", x, y, z);
}

void Node::printVtk(FILE* fid)
{
    fprintf(fid,"%f %f %f\n", x, y, z);
}