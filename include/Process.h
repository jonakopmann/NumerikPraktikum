#ifndef PROCESS_H
#define PROCESS_H

#include "Polynom.h"

#define SYMMETRY_MAIN 254
#define SYMMETRY_PILOT 248

#define N 10
#define H 0.1

void Smooth(double* values, int count, int degree);

double* Interpolate(double* values, int symmetry);

double Convert(Polynom* polynom, int radius, int maxRadius);

#endif
