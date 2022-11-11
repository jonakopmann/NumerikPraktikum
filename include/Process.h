#ifndef PROCESS_H
#define PROCESS_H

#define SYMMETRY_MAIN 254
#define SYMMETRY_PILOT 248

class Polynom
{
public:
    Polynom(long double* inCoefs, int inDegree);
    ~Polynom();
    double Function(int x);
    void Print();

private:
    int n;
    long double* coefs;
};

Polynom PolynomialFit(long double* values, int count, int degree);

double* Interpolate(double* values, int symmetry);

double* ReConstruct(double* intensity, int count, int radius);

#endif
