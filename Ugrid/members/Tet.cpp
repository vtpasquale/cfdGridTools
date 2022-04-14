#include "Tet.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace UGN = UgridNamespace;

void UGN::Tet::read(ifstream& myFileStream)
{
    string line;
    line = UGN::ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> n[2] >> n[3];
}

void UGN::Tet::print()
{
    printf("%d %d %d %d\n", n[0], n[1], n[2], n[3]);
}

void UGN::Tet::printVtk(FILE* fid)
{
    fprintf(fid,"4 %d %d %d %d\n", n[0]-1, n[1] - 1, n[2] - 1, n[3] - 1);
}