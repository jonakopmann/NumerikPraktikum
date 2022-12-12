#include <cmath>
#include <iomanip>
#include <iostream>

#include "IO/Reader.h"
#include "IO/Writer.h"
#include "Polynom.h"
#include "Process.h"
#include "Utils.h"

using namespace std;

int main()
{
    // set up cout
    cout.precision(15);
    cout.setf(ios::scientific);

#if DEBUG
    const int degree = 7;
    const char* fileName = "../FlammenbilderRohdaten/Hauptflamme.txt";
    const char* outFileName = "../FlammenbilderRohdaten/Hauptflamme_Radial.txt";
    const int symmetry = SYMMETRY_MAIN;
#else
    char* fileName;
    cout << "input file name" << endl;
    cin >> fileName;
    int degree;
    cout << "input degree" << endl;
    cin >> degree;
    const int symmetry = SYMMETRY_MAIN;
    const char* outFileName = "../FlammenbilderRohdaten/out.txt";
#endif
    
    cout << "reading in values" << endl;

    int rowCount, columnCount;
    double** transverseDistribution = ReadFile(fileName, &rowCount, &columnCount);

    int maxRad = symmetry;
    double** reconstructed = new double*[rowCount];
    
    cout << "processing values" << endl;

    long double maxDiff = -__DBL_MAX__, diff = 0;
    for (int i = 0; i < rowCount; i++)
    {
        double* row = transverseDistribution[i];

        double* interpolated = Interpolate(row, symmetry);

        Smooth(interpolated, symmetry + 1, 9);
        
        Polynom* polynom = PolynomialFit(interpolated, symmetry + 1, degree);

#if DEBUG
        //polynom->Print();
        
        // diff between polynom and real values
        for (int i = 0; i < symmetry + 1; i++)
        {
            diff += abs(interpolated[i] - polynom->Function(i));
            //if (diff > maxDiff)
            {
                //maxDiff = diff;
            }
        }
#endif
        
        reconstructed[i] = new double[maxRad * 2 + 1];
        for (int r = 0; r <= maxRad; r++)
        {
            reconstructed[i][maxRad - r] = Check(Convert(polynom, r, maxRad));
            reconstructed[i][maxRad + r] = reconstructed[i][maxRad - r];
        }

        delete polynom;
        
        delete[] interpolated;
    }

#if DEBUG
    cout << "diff: " << diff / (rowCount * symmetry + 1) << endl;
#endif

    WriteFile(outFileName, reconstructed, rowCount, maxRad * 2 + 1);
    
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
