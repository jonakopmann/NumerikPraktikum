#include <fstream>

#include "IO/Reader.h"

using namespace std;

/// @brief Read 512 lines from a file with 512 values.
/// @param fileName Name of the file which gets read.
/// @return The values as a double matrix.
double** ReadFile(const char* fileName)
{
    ifstream stream;
    stream.open(fileName);

    if (stream.fail())
    {
        throw runtime_error("Could not open file: " + string(fileName));
    }
    
    // skip header for now, maybe later parse it for better compatibility
    string temp;
    getline(stream, temp);
    getline(stream, temp);
    getline(stream, temp);
    getline(stream, temp);
    getline(stream, temp);

    // parse values into double**
    double** retVal = new double*[512];

    for (int i = 0; i < 512; i++)
    {
        retVal[i] = new double[512];
        for (int j = 0; j < 512; j++)
        {
            stream >> retVal[i][j];
        }
    }
    
    stream.close();
    return retVal;
}

/// @brief Reads one line from a file.
/// @param fileName Name of the file which gets read.
/// @return The values as a double array.
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
