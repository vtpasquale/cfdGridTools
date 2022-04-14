#include <fstream>
#include <string>
#include "blazekReadline.h"
using namespace std;
namespace PLTN = PltNamespace;

// From Blazek
string PLTN::ReadLine(ifstream& stream)
{
    string str;
    string::size_type ic;

    if (stream.good())
    {
        getline(stream, str);

        // get rid of comment
        ic = str.find_first_of('#');
        if (ic != string::npos) str.erase(str.begin() + ic, str.end());

        // get rid of leading spaces
        ic = str.find_first_not_of(' ');
        if ((int)ic > 0) str.erase(str.begin(), str.begin() + ic);

        // get rid of trailing spaces
        ic = str.find_last_not_of(' ');
        if (ic != string::npos) str.erase(str.begin() + ic + 1, str.end());

    }
    else throw runtime_error("could not read line from file.");

    return str;
}