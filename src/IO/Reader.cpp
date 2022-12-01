#include <fstream>

#include "IO/Reader.h"

using namespace std;

double** ReadFile(const char* fileName, int* outRowCount, int* outColumnCount)
{
    ifstream stream;
    stream.open(fileName);

    if (stream.fail())
    {
        throw runtime_error("Could not open file: " + string(fileName));
    }

    // description
    string temp;
    getline(stream, temp);
    getline(stream, temp);
    getline(stream, temp);
    // get matrix size
    char c;
    stream >> c >> c;
    stream >> *outRowCount;
    stream >> c >> c >> c;
    stream >> *outColumnCount;
    getline(stream, temp);
    getline(stream, temp);

    // parse values into double**
    double** retVal = new double*[*outRowCount];

    for (int i = 0; i < *outRowCount; i++)
    {
        retVal[i] = new double[*outColumnCount];
        for (int j = 0; j < *outColumnCount; j++)
        {
            stream >> retVal[i][j];
        }
    }
    
    stream.close();
    return retVal;
}

double* ReadTestLine(const char* fileName)
{
    ifstream stream;
    stream.open(fileName);

    if (stream.fail())
    {
        throw runtime_error("Could not open file: " + string(fileName));
    }

    // parse values into double*
    double* retVal = new double[512];

    for (int i = 0; i < 512; i++)
    {
        stream >> retVal[i];
    }
    
    stream.close();
    return retVal;
}
