#include <fstream>

#include "IO/Writer.h"

using namespace std;

void WriteFile(const char* fileName, long double** values, int counti, int countj)
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

void WritePlotFile(const char* fileName, const char* dataFileName, const char* outFileName, int rowCount, int columnCount)
{
    ofstream stream;
    stream.open(fileName);
    stream << "#!/usr/bin/gnuplot" << endl;
    stream << "set terminal pngcairo enhanced"<< endl;
    stream << "set xrange [0:" << columnCount <<"]"<< endl;
    stream << "set yrange [0:" << rowCount<< "]" << endl;
    stream << endl;

    stream << "set cblabel \"Intensity\"" << endl;
    stream << "set xtics nomirror" << endl;
    stream << "set ytics nomirror" << endl;
    stream << "set xtics out" << endl;
    stream << "set ytics out" << endl;
    stream << "set xlabel 'Position/Pixel'" << endl;
    stream << "set ylabel 'Hight/Pixel'" << endl;
    stream << endl;

    stream << "set title \"Test\"" << endl;
    stream << "set out \""  << outFileName << "\"" << endl;
    stream << "plot \"" << dataFileName << "\" matrix with image" << endl;
    stream.close();
}


    
