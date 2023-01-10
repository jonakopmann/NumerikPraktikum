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

/// @brief 
/// @param x 
/// @return 
long double Polynom::Function(long double x)
{
    double retVal = 0;
    for (int i = 0; i < m_n; i++)
    {
        retVal += m_coefs[i] * pow(x, i);
    }
    return retVal;
}

/// @brief 
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
Polynom* PolynomialFit(long double* values, int count, int degree)
{       
    long double* X = new long double[2 * degree + 1];
    for (int i = 0; i < 2 * degree + 1;i++)
    {
        X[i] = 0;
        for (int j = 0; j < count; j++)
        {
            //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
            X[i] += pow(count -1 - j, i);
        }
    }

    //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
    long double** B = new long double*[degree + 1];
    for (int i = 0;i <= degree;i++)
    {
        B[i] = new long double[degree + 2];
        for (int j = 0;j <= degree;j++)
        {
            //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
            B[i][j] = X[i + j];
        }
    }
    delete[] X;
    
    for (int i = 0; i < degree + 1; i++)
    {
        B[i][degree + 1] = 0;
        for (int j = 0; j < count;j++)
        {
            //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
            B[i][degree + 1] += pow(count - 1 - j, i) * values[j];
        }
    }

    int n = degree + 1;

    //From now Gaussian Elimination starts to solve the set of linear equations
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


    //loop to perform the gauss elimination
    for (int i = 0; i < n - 1; i++)
    {
        for (int k = i + 1;k < n;k++)
        {
            long double t = B[k][i] / B[i][i];
            //make the elements below the pivot elements equal to zero or elimnate the variables
            for (int j = 0; j <= n; j++)
            {
                B[k][j] = B[k][j] - t * B[i][j];
            }
        }
    }

    //back-substitution
    long double* coefs = new long double[n];
    for (int i = 0; i < n; i++)
    {
        coefs[i] = 0;
    }
    for (int i = n - 1;i >= 0;i--)
    {
        //x is an array whose values correspond to the values of x,y,z..
        coefs[i] = B[i][n];

        //make the variable to be calculated equal to the rhs of the last equation
        for (int j = 0;j < n;j++)
        {
            //then subtract all the lhs values except the coefficient of the variable whose value is being calculated
            if (j != i)
            {
                coefs[i] -= B[i][j] * coefs[j];
            }
        }
        //now finally divide the rhs by the coefficient of the variable to be calculated
        coefs[i] = coefs[i] / B[i][i];
    }

    for (int i = 0; i < degree + 1; i++)
    {
        delete[] B[i];
    }
    delete[] B;
    
    return new Polynom(coefs, degree);
}
