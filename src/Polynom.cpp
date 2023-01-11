#include <cmath>
#include <iomanip>
#include <iostream>
#include <float.h>

#include "Polynom.h"
#include "Utils.h"

Polynom::Polynom(long double* inCoefs, int inDegree)
{
    m_coefs = inCoefs;
    m_n = inDegree + 1;
}

Polynom::~Polynom()
{
    delete[] m_coefs;
}

/// @brief Berechnet den Wert der Funktion an der Stelle x
/// @param x ist Stelle, an der Funktionswert berechnet werden soll
/// @return Funktionswert an der Stelle x
long double Polynom::Function(long double x)
{
    double retVal = 0;
    for (int i = 0; i < m_n; i++)
    {
        retVal += m_coefs[i] * pow(x, i);
    }
    return retVal;
}

/// @brief Gibt Funktionsgleichung aus
void Polynom::Print()
{
    std::cout << m_coefs[0];
    for (int i = 1; i < m_n; i++)
    {
        std::cout << " + " << m_coefs[i] << " * x^" << i;
    }
    std::cout << std::endl;
}

/// @brief Legt ein Polynom durch die Werte
/// @param values eingegebene Werte
/// @param count Anzahl der Werte
/// @param degree Polynomgrad
/// @return Pointer zum Polynom
Polynom* PolynomialFit(long double* values, int count, int degree)
{       
    long double* X = new long double[2 * degree + 1];
    for (int i = 0; i < 2 * degree + 1;i++)
    {
        X[i] = 0;
        for (int j = 0; j < count; j++)
        {
            //Array speichert individuelle x-Werte (x-Werte invertieren, da Radius in der Mitte startet)
            X[i] += pow(count -1 - j, i);
        }
    }

    //B ist die Matrix, die die Werte speichert. Letzte Spalte für die y-Werte
    long double** B = new long double*[degree + 1];
    for (int i = 0;i <= degree;i++)
    {
        B[i] = new long double[degree + 2];
        for (int j = 0;j <= degree;j++)
        {
            B[i][j] = X[i + j];
        }
    }
    delete[] X;

    // Letze Spale mit sigma(xj^i * yj) befüllen
    for (int i = 0; i < degree + 1; i++)
    {
        B[i][degree + 1] = 0;
        for (int j = 0; j < count;j++)
        {
            B[i][degree + 1] += pow(count - 1 - j, i) * values[j];
        }
    }

    int n = degree + 1;

    // Gaußsches Eliminationsverfahren startet, hier: größter Wert als Pivot-Element wählen
    for (int i = 0; i < n; i++)
    {
        for (int k = i + 1; k < n; k++)
        {
            if (B[i][i] < B[k][i])
            {
                for (int j = 0; j <= n; j++)
                {
                    long double temp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = temp;
                }
            }
        }
    }


    // Elemente unter dem Pivotelement zu Null setzen
    for (int i = 0; i < n - 1; i++)
    {
        for (int k = i + 1;k < n;k++)
        {
            long double t = B[k][i] / B[i][i];
           
            for (int j = 0; j <= n; j++)
            {
                B[k][j] -= t * B[i][j];
            }
        }
    }

    //Rücksubstitution
    long double* coefs = new long double[n];
    for (int i = 0; i < n; i++)
    {
        coefs[i] = 0;
    }
    for (int i = n - 1;i >= 0;i--)
    {
        coefs[i] = B[i][n];

        //Werte über Pivo-Elementen zu Null setzen
        for (int j = 0;j < n;j++)
        {
            if (j != i)
            {
                coefs[i] -= B[i][j] * coefs[j];
            }
        }
        // Pivotelement einsetzen
        coefs[i] /= B[i][i];
    }

    for (int i = 0; i < degree + 1; i++)
    {
        delete[] B[i];
    }
    delete[] B;
    
    return new Polynom(coefs, degree);
}
