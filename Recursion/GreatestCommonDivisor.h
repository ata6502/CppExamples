#pragma once

#include <iostream>

using std::cout;
using std::endl;

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

void CalculateGreatestCommonDivisor()
{
    cout << "*** Greatest Common Divisor ***" << endl;

    // 48/18: quotient = 2, reminder = 12
    // 18/12: quotient = 1, reminder = 6
    // 12/6:  quotient = 2, reminder = 0
    // 6 is GDC
    cout << "GCD(48,18) = " << gcd(48, 18) << endl;

    // 45/60: quotient = 0, reminder = 45
    // 60/45: quotient = 1, reminder = 15
    // 45/15: quotient = 3, reminder = 0
    // 15 is GDC
    cout << "GCD(45,60) = " << gcd(45, 60) << endl;

    cout << "GCD(60,45) = " << gcd(60, 45) << endl;

    cout << endl;
}




