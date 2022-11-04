#include <fstream>
#include <iostream>
#include "IO/Reader.h"

using namespace std;

double** ReadFile(const char* fileName)
{
    ifstream stream;
    stream.open(fileName);
    
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