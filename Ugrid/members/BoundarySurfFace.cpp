#include "BoundarySurfFace.h"
#include "blazekReadline.h"
#include <fstream>
#include <sstream>
using namespace std;
namespace UGN = UgridNamespace;

void UGN::BoundarySurfFace::read(ifstream& myFileStream)
{
    string line;
    line = UGN::ReadLine(myFileStream);
    stringstream(line) >> n;
}

void UGN::BoundarySurfFace::print()
{
    printf("%d\n", n);
}