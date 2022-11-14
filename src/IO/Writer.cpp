#include <fstream>

#include "IO/Writer.h"

using namespace std;

void WriteFile(const char* fileName, double** values, int counti, int countj)
{
    ofstream stream;
    stream.open(fileName);

    if (stream.fail())
    {
        throw runtime_error("Could not open file: " + string(fileName));
    }

    for (int i = 0; i < counti; i++)
    {
        for (int j = 0; j < countj; j++)
        {
            stream << values[i][j] << " ";
        }
        stream << endl;
    }
    stream.close();
}