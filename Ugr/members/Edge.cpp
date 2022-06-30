#include "Edge.h"
#include "blazekReadline.h"
#include <sstream>
using namespace std;
namespace UGRN = UgrNamespace;

void UGRN::Edge::read(ifstream& myFileStream)
{
    string line;
    line = UGRN::ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1];
    n[0]--;
    n[1]--;
}

void UGRN::Edge::write(FILE* fid)
{
    fprintf(fid,"%d %d\n", n[0]+1, n[1]+1);
}