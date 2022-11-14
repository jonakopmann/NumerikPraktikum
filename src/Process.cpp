#include <cmath>
#include <iostream>

#include "Process.h"

// difference quotient
double diff(double x, Polynom* polynom)
{
    return (polynom->Function(x + H) - polynom->Function(x - H)) / (2 * H);
}

double func(double y, double r, Polynom* polynom)
{
    return diff(y, polynom) / sqrt((pow(y, 2) - pow(r, 2)));
}

double midpoint(double a, double b, double n, Polynom* polynom)
{   
    double h, y, retVal = 0.0;
    
    h = (b - a) / n;
    if (h == 0)
    {
        // a and b are the same
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        y = a - h / 2 + i * h;
        retVal += func(y, a, polynom);
    }
    
    return h * retVal;
}

double* Interpolate(double* values, int symmetry)
{
    double* retVal = new double[symmetry + 1];

    for (int i = 0; i <= symmetry; i++)
    {
        retVal[symmetry - i] = (values[symmetry + i] + values[symmetry - i]) / 2.0;
    }

    return retVal;
}

double Convert(Polynom* polynom, int radius, int maxRadius)
{
    const double factor = -1.0 / M_PI;

    return factor * midpoint(radius, maxRadius, N, polynom);
}
