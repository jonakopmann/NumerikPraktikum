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
    const double n = 512;
    const char* outFileName = "../FlammenbilderRohdaten/out.txt";
    const int symmetry = SYMMETRY_MAIN;
#else
    char* fileName;
    cout << "input file name" << endl;
    cin >> fileName;
    int degree;
    cout << "input degree" << endl;
    cin >> degree;
#endif

    double** valueArray = ReadFile(fileName);

    int maxRad = symmetry;
    double** reconstructed = new double*[512];

    cout << "reading in values" << endl;
    for (int i = 0; i < 512; i++)
    {
        double* values = valueArray[i];

        double* interpolated = Interpolate(values, symmetry);

        Polynom* polynom = PolynomialFit(interpolated, symmetry + 1, degree);

        /*for (int i = 0; i < SYMMETRY_MAIN + 1; i++)
        {
            cout << interpolated[i] << "    " << polynom->Function(i) << endl;
        }*/

#if DEBUG
        polynom->Print();
#endif
        cout << "processing values" << endl;
        reconstructed[i] = new double[maxRad * 2 + 1];
        for (int r = 0; r <= maxRad; r++)
        {
            reconstructed[i][maxRad - r] = Check(Convert(polynom, r, maxRad));
            reconstructed[i][maxRad + r] = reconstructed[i][maxRad - r];
        }

        delete polynom;

        delete[] interpolated;
    }
    
    WriteFile(outFileName, reconstructed, 512, maxRad * 2 + 1);

    cout << "data written to " << outFileName << endl;
    
    for (int i = 0; i < 512; i++)
    {
        delete[] valueArray[i];
        delete[] reconstructed[i];
    }
    delete[] valueArray;
    delete[] reconstructed;

    return 0;
}
