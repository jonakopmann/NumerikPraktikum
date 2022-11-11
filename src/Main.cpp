#include <iostream>
#include <iomanip>
#include "Process.h"
#include "Polynom.h"
#include "IO/Reader.h"

using namespace std;

int main()
{
    // set up cout
    cout.precision(15);
    cout.setf(ios::scientific);

#if DEBUG
    const int degree = 3;
    const char* fileName = "../FlammenbilderRohdaten/Zeile170.txt";
#else
    char* fileName;
    cout << "input file name" << endl;
    cin >> fileName;
    int degree;
    cout << "input degree" << endl;
    cin >> degree;
#endif

    double* values = ReadTestLine(fileName);

    Polynom* polynom = PolynomialFit(values, 512, degree);
#if DEBUG
    polynom->Print();
#endif

    delete polynom;

    return 0;
}
