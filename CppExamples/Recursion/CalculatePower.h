#pragma once

#include <iostream>

using std::cout;
using std::endl;

long int power(int base, int exp)
{
    // terminating condition
    if (exp == 1)
        return base;

    // recursion step
    return base * power(base, exp - 1);
}

// CalculatePower calculates the power base^exp.
void CalculatePower()
{
    cout << "*** Calculate Power ***" << endl;

    cout << "2^8 = " << power(2, 8) << endl;
    cout << "5^4 = " << power(5, 4) << endl;
    cout << "11^2 = " << power(11, 2) << endl;

    cout << endl;
}

