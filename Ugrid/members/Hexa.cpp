#include "Hexa.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace UGN = UgridNamespace;

void UGN::Hexa::read(ifstream& myFileStream)
{
    string line;
    line = UGN::ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> n[2] >> n[3] >> n[4] >> n[5] >> n[6] >> n[7];
}

void UGN::Hexa::print()
{
    printf("%d %d %d %d %d %d %d %d\n", n[0], n[1], n[2], n[3], n[4], n[5], n[6], n[7]);
}

void UGN::Hexa::printVtk(FILE* fid)
{
    fprintf(fid,"8 %d %d %d %d %d %d %d %d\n", n[0]-1, n[1] - 1, n[2] - 1, n[3] - 1, n[4] - 1, n[5] - 1, n[6] - 1, n[7] - 1);
}