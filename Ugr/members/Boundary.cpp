#include "Boundary.h"
#include "blazekReadline.h"
#include <sstream>
using namespace std;
namespace UGRN = UgrNamespace;

void UGRN::Boundary::read(ifstream& myFileStream)
{
    string line;
    line = UGRN::ReadLine(myFileStream);
    stringstream(line) >> type >> lastFace >> lastNode;

    lastFace--;  // Change from base 1 to base 0
    lastNode--;

    name = UGRN::ReadLine(myFileStream);
}

void UGRN::Boundary::write(FILE* fid)
{
    fprintf(fid,"%d %d %d\n", type , lastFace+1 , lastNode+1 );
    fprintf(fid,"%s\n", name.c_str() );
}