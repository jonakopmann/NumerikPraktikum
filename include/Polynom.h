#ifndef POLYNOM_H
#define POLYNOM_H

class Polynom
{
public:
    Polynom(long double* inCoefs, int inDegree);
    ~Polynom();
    double Function(int x);
    void Print();
    double GetH();
    void SetH(double value);

private:
    int m_n;
    long double* m_coefs;
    double m_h;
};

Polynom* PolynomialFit(double* values, int count, int degree);

#endif
