#include "Pent6.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;

void Pent6::read(ifstream& myFileStream)
{
    string line;
    line = ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> n[2] >> n[3] >> n[4] >> n[5];
}

void Pent6::print()
{
    printf("%d %d %d %d %d %d\n", n[0], n[1], n[2], n[3], n[4], n[5]);
}

void Pent6::printVtk(FILE* fid)
{
    fprintf(fid,"6 %d %d %d %d %d %d\n", n[0]-1, n[1] - 1, n[2] - 1, n[3] - 1, n[4] - 1, n[5] - 1);
}