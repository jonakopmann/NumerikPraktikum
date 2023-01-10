#include <iomanip>
#include <iostream>

#include "IO/Reader.h"
#include "IO/Writer.h"
#include "Polynom.h"
#include "Process.h"
#include "Utils.h"

using namespace std;

void printProgress(double progress, int barWidth)
{
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
        if (i <= pos)
        {
            std::cout << "|";
        }
        else
        {
            std::cout << " ";
        }
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
    if (progress == 1)
    {
        std::cout << std::endl;
    }
}

int main()
{
    // set up cout
    cout.precision(15);
    cout.setf(ios::scientific);

#if DEBUG
    const int degree = 9;
    const char* fileName = "../FlammenbilderRohdaten/Hauptflamme.txt";
    const int symmetry = SYMMETRY_MAIN;
    const int deleteValues = 10;
    const int width = 9;
#else
    // name of the file where the data is stored
    char* fileName;
    cout << "input file name" << endl;
    cin >> fileName;

    // degree of the polynom
    int degree;
    cout << "input degree for polynom" << endl;
    cin >> degree;

    // width for smoothing
    int width;
    cout << "input width for smoothing" << endl;
    cin >> width;

    // number of values from the middle which should get deleted
    int deleteValues;
    cout << "input deleteValues" << endl;
    cin >> deleteValues;

    // symmetry axis of the flame
    int symmetry;
    if (string(fileName).find("Hauptlamme") != -1)
    {
        symmetry = SYMMETRY_MAIN;
    }
    else
    {
        symmetry = SYMMETRY_PILOT;
    }
#endif

    // name of the file that gets written with the newly calculated values
    const char* outFileName = "../FlammenbilderRohdaten/out.txt";
    
    cout << "reading in values ...";

    // read the values of the distribution from the file into an array and parse the row/column count
    int rowCount, columnCount;
    long double** transverseDistribution = ReadFile(fileName, &rowCount, &columnCount);

    // the maximum radius is the same as the symmetry axis
    int maxRad = symmetry;

    // array to hold in the reconstructed distribution
    long double** reconstructed = new long double* [rowCount];
    
    cout << "\rprocessing values:" << endl;

    for (int i = 0; i < rowCount; i++)
    {
        // progress bar
        printProgress(i / double(rowCount - 1), 70);
        
        long double* row = transverseDistribution[i];

        long double* interpolated = Interpolate(row, symmetry);

        Smooth(interpolated, symmetry + 1, 9);

        Polynom* polynom = PolynomialFit(interpolated, symmetry + 1, degree);

        reconstructed[i] = new long double[maxRad * 2 + 1];
        for (int r = 0; r <= maxRad; r++)
        {
            if (r < deleteValues)
            {
                reconstructed[i][maxRad - r] = 0;
            }
            else
            {
                reconstructed[i][maxRad - r] = Check(Convert(polynom, r, maxRad));
            }
            reconstructed[i][maxRad + r] = reconstructed[i][maxRad - r];
        }

        delete polynom;
        
        delete[] interpolated;
    }

    // write reconstructed distribution to file
    WriteFile(outFileName, reconstructed, rowCount, maxRad * 2 + 1);

    // write gnuplot script
    WritePlotFile("../FlammenbilderRohdaten/gnuplot", outFileName, "test.png", rowCount, maxRad * 2 + 1);

    cout << "data written to " << outFileName << endl;
    
    for (int i = 0; i < rowCount; i++)
    {
        delete[] transverseDistribution[i];
        delete[] reconstructed[i];
    }
    delete[] transverseDistribution;
    delete[] reconstructed;

    return 0;
}
