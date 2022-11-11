#ifndef POLYNOM_H
#define POLYNOM_H

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

#endif
