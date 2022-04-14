#include "Pent5.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace UGN = UgridNamespace;

void UGN::Pent5::read(ifstream& myFileStream)
{
    string line;
    line = UGN::ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> n[2] >> n[3] >> n[4];
}

void UGN::Pent5::print()
{
    printf("%d %d %d %d %d\n", n[0], n[1], n[2], n[3], n[4]);
}

void UGN::Pent5::printVtk(FILE* fid)
{
    fprintf(fid,"5 %d %d %d %d %d\n", n[0]-1, n[1] - 1, n[2] - 1, n[3] - 1, n[4] - 1);
}