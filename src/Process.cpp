#include <math.h>
#include <iostream>

#include "Process.h"

long double avg(long double* values, int index, int n)
{
    long double retVal = 0.0;
    for (int i = -n; i <= n; i++)
    {
        retVal += values[index + i];
    }
    return (1.0 / (2 * n + 1)) * retVal;
}

// difference quotient
long double diff(long double x, Polynom* polynom)
{
    return (polynom->Function(x + H) - polynom->Function(x - H)) / (2 * H);
}

long double func(long double y, long double r, Polynom* polynom)
{
    long double d = diff(y, polynom);
    long double t = sqrt(y * y - r * r);
    return d / t;
}

long double midpoint(long double a, long double b, Polynom* polynom)
{   
    long double retVal = 0.0;

    for (long double y = a + DY; y < b; y += DY)
    {
        retVal += DY * func(y, a, polynom);
    }
    
    return retVal;
}

/// @brief 
/// @param values 
/// @param symmetry 
/// @return 
long double* Interpolate(long double* values, int symmetry)
{
    long double* retVal = new long double[symmetry + 1];

    for (int i = 0; i <= symmetry; i++)
    {
        retVal[symmetry - i] = (values[symmetry + i] + values[symmetry - i]) / 2.0;
    }

    return retVal;
}

/// @brief 
/// @param values 
/// @param count 
/// @param width 
void Smooth(long double* values, int count, int width)
{
    int n = (width - 1) / 2;
    for (int i = n; i < count - n; i++)
    {
        values[i] = avg(values, i, n);
    }
}

/// @brief 
/// @param polynom 
/// @param radius 
/// @param maxRadius 
/// @return 
long double Convert(Polynom* polynom, int radius, int maxRadius)
{
    const long double factor = -1.0 / M_PI;

    return factor * midpoint(radius, maxRadius, polynom);
}
