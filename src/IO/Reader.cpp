#include <fstream>
#include <iostream>
#include <vector>

#include "IO/Reader.h"

using namespace std;

/// @brief Reads all values from a file.
/// @param fileName Name of the file which gets read.
/// @param outRowCount The row count of the matrix.
/// @param outColumnCount The column count of the matrix.
/// @return The values as a double matrix.
long double** ReadFile(string fileName, int* outRowCount, int* outColumnCount)
{
    ifstream stream;
    stream.open(fileName);

    if (stream.fail())
    {
        throw runtime_error("Could not open file: " + fileName);
    }
    
    // Beschreibung überspringen (5 Zeilen)
    string temp;
    getline(stream, temp);
    getline(stream, temp);
    getline(stream, temp);
    getline(stream, temp);
    getline(stream, temp);

    std::streampos startPos = stream.tellg();     

    // Reihenanzahl bestimmen
    *outRowCount = 0;
    while (getline(stream, temp))
    {
        (*outRowCount)++;
    }

    // Werte in Vektor einlesen und Spaltenanzahl bestimmen
    stream.clear();
    stream.seekg(startPos);            
    std::vector<double> values;

    double d;
    while (stream >> d)
    {
        values.push_back(d);
    }
    if ((values.size() % (*outRowCount)) != 0)
    {
        throw runtime_error("input file does not have the right format!");
    }
    *outColumnCount = values.size() / *outRowCount;

    stream.close();

    // Werte aus Vektor in Array schreiben
    long double** retVal = new long double*[*outRowCount];
    for (int i = 0, t = 0; i < *outRowCount; i++)
    {
        retVal[i] = new long double[*outColumnCount];
        for (int j = 0; j < *outColumnCount; j++)
        {
            retVal[i][j] = values.at(t++);
        }
    }

    return retVal;
}
