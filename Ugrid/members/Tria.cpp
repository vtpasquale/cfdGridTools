#include "Tria.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace UGN = UgridNamespace;

void UGN::Tria::read(ifstream& myFileStream)
{
    string line;
    line = UGN::ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> n[2];
}

void UGN::Tria::print()
{
    printf("%d %d %d\n", n[0], n[1], n[2]);
}

void UGN::Tria::printVtk(FILE* fid)
{
    fprintf(fid,"3 %d %d %d\n", n[0]-1, n[1]-1, n[2]-1);
}