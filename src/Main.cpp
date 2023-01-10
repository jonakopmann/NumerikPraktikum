#include <iomanip>
#include <iostream>

#include "IO/Reader.h"
#include "IO/Writer.h"
#include "Polynom.h"
#include "Process.h"
#include "Utils.h"

using namespace std;
// Funktion für Progressbar
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
    cout.precision(15);
    cout.setf(ios::scientific);

#if DEBUG
    const int degree = 9;
    string fileName = "../FlammenbilderRohdaten/Hauptflamme.txt";
    const int symmetry = SYMMETRY_MAIN;
    const int deleteValues = 10;
    const int width = 9;
#else
    // Name des Files, wo Werte gespeichert werden
    string fileName;
    cout << "input file name" << endl;
    cin >> fileName;

    // Polynomgrad
    int degree;
    cout << "input degree for polynom" << endl;
    cin >> degree;

    // Breite für Glättung
    int width;
    cout << "input width for smoothing" << endl;
    cin >> width;

    // Anzahl der Werte an der Symmetrieachse, die gelöscht werden sollen
    int deleteValues;
    cout << "input deleteValues" << endl;
    cin >> deleteValues;

    // Symmetrieachse der Flamme
    int symmetry;
    if (fileName.find("Hauptflamme") != -1)
    {
        symmetry = SYMMETRY_MAIN;
    }
    else
    {
        symmetry = SYMMETRY_PILOT;
    }
#endif

    // Name der Datei der Radialverteilung
    const char* outFileName = "../FlammenbilderRohdaten/out.txt";
    
    cout << "reading in values ...";

    // Herausfinden der Dimension und Einlesen der Werte in ein Array für Querverteilung
    int rowCount, columnCount;
    long double** transverseDistribution = ReadFile(fileName, &rowCount, &columnCount);
    
    // Maximaler Radius und Symmetrieachse stimmen überein
    int maxRad = symmetry;

    // Array für die Radialverteilung
    long double** reconstructed = new long double* [rowCount];
    
    cout << "\rprocessing values:" << endl;

    for (int i = 0; i < rowCount; i++)
    {
        // progress bar
        printProgress(double(i + 1) / rowCount, 70);

        // Werte Mitteln und Halbieren
        long double* interpolated = Interpolate(transverseDistribution[i], symmetry);

        // Glättung
        Smooth(interpolated, symmetry + 1, width);

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
