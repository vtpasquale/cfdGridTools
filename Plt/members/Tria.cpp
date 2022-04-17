#include "Tria.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace PLTN = PltNamespace;

void PLTN::Tria::read(ifstream& myFileStream)
{
    string line;
    line = PLTN::ReadLine(myFileStream);
    stringstream(line) >> id >> n[0] >> n[1] >> n[2];
}

void PLTN::Tria::write(FILE* fid)
{
    fprintf(fid,"%d %d %d %d\n", id, n[0], n[1], n[2]);
}

void PLTN::Tria::printVtk(FILE* fid)
{
    fprintf(fid,"3 %d %d %d\n", n[0]-1, n[1]-1, n[2]-1);
}