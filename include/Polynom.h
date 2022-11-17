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
    int m_n;
    long double* m_coefs;
};

Polynom* PolynomialFit(double* values, int count, int degree);

#endif
