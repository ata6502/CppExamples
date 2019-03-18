#pragma once

#include <iostream>
#include <iomanip>  // setiosflags, setprecision
#include <limits>   // numeric_limits
#include <cmath>    // M_PI, M_E, etc.

using std::cout;
using std::endl;
using std::setiosflags;
using std::setprecision;
using std::setw;
using std::ios;

/*
    In C++, the size of int may not be four bytes.
    sizeof returns the size of int (of type size_t).

    <cstdint> defines integral types of fixed sizes.
    Use it to create portable code.

    int32_t is guaranteed to be a signed 32-bit integer type.
    uint64_t is guaranteed to be an unsigned 64-bit integer type.

    float is also not standardized, but on desktop is usually 32-bit.
    double is 64-bit.

    Useful mathematical functions:
    ceil(x)     rounds x to the smallest integer not less than x
    floor(x)    rounds x to the largest integer not greater than x
    fabs(x)     an absolute value of x
    fmod(x)     remainder of x/y as a floating point number
    log(x)      natural logarithm of x
    log10(x)    logarithm of x (base 10)
    pow(x, y)   x raised to power y
    sqrt(x)     square root of x
    sin(x)      example: sin(M_PI / 2)
*/

namespace NumbersExamples
{
    void Size()
    {
        // pass the type
        size_t a = sizeof(int);

        // pass a variable
        int n = 0;
        size_t b = sizeof(n);

        cout << a << " " << b << " ";
    }

    void RoundAndTruncate()
    {
        double r = 2.5176;

        cout << setprecision(4);

        // Round the number to the nearest tenth.
        cout << floor(r * 10 + .5) / 10 << " ";           // 2.5000

        // Round the number to the nearest hundreth.
        cout << floor(r * 100 + .5) / 100 << " ";         // 2.5200

        // Round the number to the nearest thousandth.
        cout << floor(r * 1000 + .5) / 1000 << " ";       // 2.5180

        // Truncate the number to the nearest hundreth.
        cout << floor(r * 100) / 100 << " ";              // 2.5100

        // ceil(x) - rounds x to the smallest integer not less than x.
        cout << setiosflags(ios::fixed | ios::showpoint) << setprecision(1)
            << "ceil(9.2)=" << ceil(9.2) << " "      // 10.0
            << "ceil(-9.8)=" << ceil(-9.8) << " ";   // -9.0

        // floor(x) - rounds x to the largest integer not greater than x.
        cout << setiosflags(ios::fixed | ios::showpoint) << setprecision(1)
            << "floor(9.2)=" << floor(9.2) << " "    // 9.0
            << "floor(-9.8)=" << floor(-9.8) << " "; // -10.0
    }

    void NumericLimits()
    {
        int maxInt = std::numeric_limits<int>::max();
        float maxFloat = std::numeric_limits<float>::max();
        double maxDouble = std::numeric_limits<double>::max();
        bool isCharSigned = std::numeric_limits<char>::is_signed;
    }

    void ShowDecimalDigits()
    {
        int n = 8125; // the number
        int d1, d2, d3, d4; // the digits

        // Method #1
        d1 = n / 1000;
        d2 = n % 1000 / 100;
        d3 = n % 100 / 10;
        d4 = n % 10;
        cout << d1 << d2 << d3 << d4 << " ";

        // Method #2  
        d4 = n % 10;
        n /= 10;
        d3 = n % 10;
        n /= 10;
        d2 = n % 10;
        n /= 10;
        d1 = n % 10;
        n /= 10;
        cout << d1 << d2 << d3 << d4 << " ";
    }

    void SwapNumbers()
    {
        int n1 = 3, n2 = 8;
        int tmp;

        // Method #1
        tmp = n1;
        n1 = n2;
        n2 = tmp;

        // Method #2
        n1 ^= n2;
        n2 ^= n1;
        n1 ^= n2;
    }

    void UserDefinedLiterals()
    {
        //
        // Complex Numbers
        //
        using namespace std::complex_literals;

        std::complex<double> a = 1. + 2i;

        // You need to write 1i not just i.
        auto b = 1i * a; // b = -2 + i

        //
        // Binary Numbers
        //
        int m = 0b001010110; // C++14

        //
        // Digit Separators
        //
        int n1 = 1'000'000; // C++14
        int n2 = 1'00'0'00'0; // the same as above; the digit separators are ignored
    }

    void Test()
    {
        Size();
        RoundAndTruncate();
        NumericLimits();
        ShowDecimalDigits();
        SwapNumbers();
        UserDefinedLiterals();
    }
}
