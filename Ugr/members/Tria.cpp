#include "Tria.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace UGRN = UgrNamespace;

void UGRN::Tria::read(ifstream& myFileStream)
{
    string line;
    line = UGRN::ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> n[2];
    n[0]--;
    n[1]--;
    n[2]--;
}

void UGRN::Tria::write(FILE* fid)
{
    fprintf(fid,"%d %d %d\n", n[0]+1, n[1]+1, n[2]+1);
}

void UGRN::Tria::printVtk(FILE* fid)
{
    fprintf(fid,"3 %d %d %d\n", n[0], n[1], n[2]);
}