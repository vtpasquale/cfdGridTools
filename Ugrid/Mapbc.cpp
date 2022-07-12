#include "Mapbc.h"
#include <sstream>
using namespace std;
using namespace UgridNamespace;

void Mapbc::read(const char* myFileName)
{
    ifstream myFileStream(myFileName);

    string line;
    line = ReadLine(myFileStream);
    stringstream(line) >> nBoundaries;
    boundary = new MapbcBoundary[nBoundaries];

    for (int i = 0; i < nBoundaries; i++)
    {
        line = ReadLine(myFileStream);
        stringstream(line) >> boundary[i].index >> boundary[i].condition >> boundary[i].name;
    }
}

void Mapbc::write(const char* myFileName)
{
    FILE* fid;
    fid = fopen(myFileName,"w");

    fprintf(fid,"%d\n", nBoundaries);

    for (int i = 0; i < nBoundaries; i++)
        fprintf(fid,"%d %d %s\n", boundary[i].index, boundary[i].condition, boundary[i].name.c_str() );

    fclose(fid);
}