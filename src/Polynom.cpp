#include <cmath>
#include <iomanip>
#include <iostream>
#include <float.h>

#include "Polynom.h"
#include "Utils.h"

void printmatrix(long double** matrix, int m, int n)
{

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << std::setw(10) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

Polynom::Polynom(long double* inCoefs, int inDegree)
{
    m_coefs = inCoefs;
    m_n = inDegree + 1;
}

Polynom::~Polynom()
{
    delete[] m_coefs;
}

double Polynom::Function(double x)
{
    double retVal = 0;
    for (int i = 0; i < m_n; i++)
    {
        retVal += m_coefs[i] * pow(x, i);
    }
    return retVal;
}

void Polynom::Print()
{
    std::cout << m_coefs[0];
    for (int i = 1; i < m_n; i++)
    {
        std::cout << " + " << m_coefs[i] << " * x^" << i;
    }
    std::cout << std::endl;
}

/// @brief 
/// @param values 
/// @param count 
/// @param degree 
/// @return 
Polynom* PolynomialFit(double* values, int count, int degree)
{
    long double** matrix = new long double* [degree + 1];
    for (int m = 0; m < degree + 1; m++)
    {
        matrix[m] = new long double[degree + 2];

        double val = 0.0;
        for (int i = 0; i < count; i++)
        {
            val += pow(i, m) * values[i];
        }
        matrix[m][degree + 1] = val;
        
        for (int n = 0; n < degree + 1; n++)
        {
            val = 0.0;
            for (int i = 0; i < count; i++)
            {
                val += pow(i, m + n);
            }
            matrix[m][n] = val;
        }
    }

    int n = degree + 1;
    for (int i = 0; i < n; i++)
    {                   
        for (int j = i + 1; j < n; j++)
        {
            if(abs(matrix[i][i]) < abs(matrix[j][i]))
            {
                for (int k = 0; k < n + 1; k++)
                {
                    // swapping mat[i][k] and mat[j][k]
                    matrix[i][k] += matrix[j][k];
                    matrix[j][k] = matrix[i][k] - matrix[j][k];
                    matrix[i][k] -= matrix[j][k];
                }
            }
        }
    }
   
    // performing Gaussian elimination
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            long double f = matrix[j][i] / matrix[i][i];
            for (int k = 0; k < n + 1; k++)
            {
                matrix[j][k] -= f * matrix[i][k];
            }
        }
    }
    
    // Backward substitution for discovering values of unknowns
    long double* coefs = new long double[degree + 1];
    for (int i = n - 1; i >= 0; i--)
    {
        coefs[i] = matrix[i][n];

        for (int j = i + 1; j < n; j++)
        {
            if (i != j)
            {
                coefs[i] -= matrix[i][j] * coefs[j];
            }
        }
        coefs[i] /= matrix[i][i];
    }

    for (int m = 0; m < degree + 1; m++)
    {
        delete[] matrix[m];
    }
    delete[] matrix;

    return new Polynom(coefs, degree);
}
