#include <math.h>
#include <iostream>

#include "Process.h"

// difference quotient
double diff(double x, Polynom* polynom)
{
    return (polynom->Function(x + H) - polynom->Function(x - H)) / (2 * H);
}

double func(double y, double r, Polynom* polynom)
{
    return diff(y, polynom) / sqrt(pow(y, 2) - pow(r, 2));
}

double midpoint(double a, double b, Polynom* polynom)
{   
    double y, retVal = 0.0;

    double h = H;
    double n = (b - a) / H;

    for (int i = 0; i < n; i++)
    {
        y = a + (i + 0.5) * h;
        retVal += func(y, a, polynom);
    }
    
    return h * retVal;
}

double avg(double* values, int index, int n)
{
    double retVal = 0.0;
    for (int i = -n; i <= n; i++)
    {
        retVal += values[index + i];
    }
    return (1.0 / (2 * n + 1)) * retVal;
}

/// @brief 
/// @param values 
/// @param count 
/// @param width 
void Smooth(double* values, int count, int width)
{
    int n = (width - 1) / 2;
    for (int i = n; i <= count - n; i++)
    {
        values[i] = avg(values, i, n);
    }
}

/// @brief 
/// @param values 
/// @param symmetry 
/// @return 
double* Interpolate(double* values, int symmetry)
{
    double* retVal = new double[symmetry + 1];

    for (int i = 0; i <= symmetry; i++)
    {
        retVal[symmetry - i] = (values[symmetry + i] + values[symmetry - i]) / 2.0;
    }

    return retVal;
}

/// @brief 
/// @param polynom 
/// @param radius 
/// @param maxRadius 
/// @return 
double Convert(Polynom* polynom, int radius, int maxRadius)
{
    const double factor = -1.0 / M_PI;

    return factor * midpoint(radius, maxRadius, polynom);
}
