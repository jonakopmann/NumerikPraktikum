#include "Process.h"

// difference quotient
double diff(int x, int h, double* values)
{
    return (values[x + h] - values[x - h]) / (2 * h);
}

double* Interpolate(double* values, int symmetry)
{
    return nullptr;
}

double* ReConstruct(double* intensity, int count, int radius)
{
    return nullptr;
}