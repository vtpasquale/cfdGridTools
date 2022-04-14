#include "Tet.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;

void Tet::read(ifstream& myFileStream)
{
    string line;
    line = ReadLine(myFileStream);
    stringstream(line) >> n[0] >> n[1] >> n[2] >> n[3];
}

void Tet::print()
{
    printf("%d %d %d %d\n", n[0], n[1], n[2], n[3]);
}

void Tet::printVtk(FILE* fid)
{
    fprintf(fid,"4 %d %d %d %d\n", n[0]-1, n[1] - 1, n[2] - 1, n[3] - 1);
}