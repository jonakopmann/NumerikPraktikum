#ifndef PROCESS_H
#define PROCESS_H

#include "Polynom.h"

#define SYMMETRY_MAIN 254
#define SYMMETRY_PILOT 248

#define H 0.1
#define DY 0.1

long double* Interpolate(long double* values, int symmetry);

void Smooth(long double* values, int count, int degree);

long double Convert(Polynom* polynom, int radius, int maxRadius);

#endif
