
#include <fstream>
#include <sstream>
#include "Node.h"
#include "blazekReadline.h"
using namespace std;
namespace UGRN = UgrNamespace;

void UGRN::Node::read(ifstream& myFileStream)
{
    string line;
    line = UGRN::ReadLine(myFileStream);
    stringstream(line) >> x >> y;
}

void UGRN::Node::write(FILE* fid)
{
    fprintf(fid,"%.8E %.8E\n", x, y);
}

void UGRN::Node::printVtk(FILE* fid)
{
    fprintf(fid,"%f %f 0.0\n", x, y);
}