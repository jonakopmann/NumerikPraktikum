#include <iomanip>
#include <iostream>

#include "IO/Reader.h"
#include "IO/Writer.h"
#include "Polynom.h"
#include "Process.h"
#include "Utils.h"

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
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

#if DEBUG
    const int degree = 9;
    std::string fileName = "../FlammenbilderRohdaten/Hauptflamme.txt";
    const int symmetry = SYMMETRY_MAIN;
    const int deleteValues = 5;
    const int width = 9;
#else
    // Name des Files, wo Werte gespeichert werden
    std::string fileName;
    std::cout << "input file name" << std::endl;
    std::cin >> fileName;

    // Polynomgrad
    int degree;
    std::cout << "input degree for polynom" << std::endl;
    std::cin >> degree;

    // Breite für Glättung
    int width;
    std::cout << "input width for smoothing" << std::endl;
    std::cin >> width;

    // Anzahl der Werte an der Symmetrieachse, die gelöscht werden sollen
    int deleteValues;
    std::cout << "input deleteValues" << std::endl;
    std::cin >> deleteValues;

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
    
    std::cout << "reading in values ...\r";

    // Herausfinden der Dimension und Einlesen der Werte in ein Array für Querverteilung
    int rowCount, columnCount;
    long double** transverseDistribution = ReadFile(fileName, &rowCount, &columnCount);
    
    // Maximaler Radius und Symmetrieachse stimmen überein
    int maxRad = symmetry;

    // Array für die Radialverteilung
    long double** reconstructed = new long double* [rowCount];
    
    std::cout.flush();
    std::cout << "processing values:" << std::endl;

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

        Smooth(reconstructed[i], maxRad * 2 + 1, width);

        delete polynom;
        
        delete[] interpolated;
    }

    // Radialverteilung in File schreiben
    WriteFile(outFileName, reconstructed, rowCount, maxRad * 2 + 1);

    // GnuPlot-Skript schreiben
    WritePlotFile("../FlammenbilderRohdaten/gnuplot", outFileName, "Radialverteilung.png", rowCount, maxRad * 2 + 1);

    system("gnuplot ../FlammenbilderRohdaten/gnuplot");

    std::cout << "data written to " << outFileName << std::endl;

    for (int i = 0; i < rowCount; i++)
    {
        delete[] transverseDistribution[i];
        delete[] reconstructed[i];
    }
    delete[] transverseDistribution;
    delete[] reconstructed;

    return 0;
}
