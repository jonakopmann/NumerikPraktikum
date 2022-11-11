#include <iostream>
#include <iomanip>
#include "Process.h"
#include "Polynom.h"

using namespace std;

int main()
{
    // set up cout
    cout.precision(15);
    cout.setf(ios::scientific);
    
    const int degree = 2;
    long double* test = new long double[6]
    {
        0, 1, 2, 3, 4, 5
    };
    Polynom polynom = PolynomialFit(test, 6, degree);
    polynom.Print();

    return 0;
}
