#include <iostream>
#include <cmath>
#include <float.h>
#include <iomanip>
#include "Polynom.h"

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
    m_h = 0.01;
}

Polynom::~Polynom()
{
    delete[] m_coefs;
}

double Polynom::Function(int x)
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

double Polynom::GetH()
{
    return m_h;
}

void Polynom::SetH(double value)
{
    m_h = value;
}

Polynom* PolynomialFit(double* values, int count, int degree)
{
    long double* X = new long double[2 * degree + 1];
    for (int i = 0; i < 2 * degree + 1;i++)
    {
        X[i] = 0;
        for (int j = 0; j < count; j++)
        {
            //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
            X[i] += pow(j, i);
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

    //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    long double* Y = new long double[degree + 1];
    for (int i = 0;i < degree + 1;i++)
    {    
        Y[i]=0;
        for (int j = 0;j < count;j++)
        {
            //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
            Y[i] += pow(j, i) * values[j];
        }
    }
    for (int i = 0; i <= degree; i++)
    {
        //load the values of Y as the last column of B(Normal Matrix but augmented)
        B[i][degree + 1] = Y[i];
    }

    delete[] Y;  

    int n = degree + 1;

    //From now Gaussian Elimination starts(can be ignored) to solve the set of linear equations (Pivotisation)
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

int argmax(int start, int end, long double** matrix, int column)
{
    long double max = -DBL_MAX;
    int index = -1;
    for (int i = start; i < end; i++)
    {
        long double d = abs(matrix[i][column]);

        if (d > max)
        {
            max = d;
            index = i;
        }
    }
    return index;
}

/*Polynom* PolynomialFit(double* values, int count, int degree)
{
    long double** matrix = new long double* [degree + 1];
    for (int m = 0; m < degree + 1; m++)
    {
        matrix[m] = new long double[degree + 2];

        double val = 0.0;
        for (int i = 0; i < count; i++)
        {
            val += pow(values[i], m) * values[i];
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
    int lead = 0; 

    while (lead < degree + 1) {
        long double d, m;

        for (int r = 0; r < degree + 1; r++)
        {
            // for each row ...
            // calculate divisor and multiplier
            d = matrix[lead][lead];
            m = matrix[r][lead] / matrix[lead][lead];

            for (int c = 0; c < degree + 2; c++)
            {
                // for each column ...
                if (r == lead)
                {
                    // make pivot = 1
                    matrix[r][c] /= d;
                }              
                else
                {
                    // make other = 0
                    matrix[r][c] -= matrix[lead][c] * m;
                }  
            }
        }

        lead++;
#if DEBUG
        printmatrix(matrix, degree + 1, degree + 2);
#endif
    }
    
    long double* coefs = new long double[degree + 1];

    for (int i = 0; i < degree + 1; i++)
    {
        coefs[i] = matrix[i][degree + 1];
    }

    return new Polynom(coefs, degree);
}*/
