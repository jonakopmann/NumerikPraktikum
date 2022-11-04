#ifndef PROCESS_H
#define PROCESS_H

#define SYMMETRY_MAIN 254
#define SYMMETRY_PILOT 248

double* Interpolate(double* values, int symmetry);

double* ReConstruct(double* intensity, int count, int radius);

#endif