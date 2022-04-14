#include "BoundarySurfFace.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;

void BoundarySurfFace::read(ifstream& myFileStream)
{
    string line;
    line = ReadLine(myFileStream);
    stringstream(line) >> n;
}

void BoundarySurfFace::print()
{
    printf("%d\n", n);
}