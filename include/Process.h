#ifndef PROCESS_H
#define PROCESS_H

#include "Polynom.h"

#define SYMMETRY_MAIN 254
#define SYMMETRY_PILOT 248

#define N 500
#define H 0.01

double* Interpolate(double* values, int symmetry);

double Convert(Polynom* polynom, int radius, int maxRadius);

#endif
