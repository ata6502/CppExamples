#pragma once

#include <iostream>

using std::cout;
using std::endl;

int factorial(int n)
{
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

void CalculateFactorial()
{
    cout << "*** Calculate Factorial ***" << endl;

    cout << "7! = " << factorial(7) << endl;
    cout << "10! = " << factorial(10) << endl;
    cout << "13! = " << factorial(13) << endl;

    cout << endl;
}

unsigned long visualize(unsigned long n)
{
    static int i = 0; // keep "function memory" - the recursion step
    unsigned long f;

    for (int j = 1; j <= i; j++) cout << "|  ";
    cout << "call factorial(" << n << ")" << endl;
    i++;
    if (n <= 1L)
    {
        for (int j = 1; j <= i - 1; j++) cout << "|  ";
        i--;
        cout << "return 1 = factorial(1)" << endl;
        return 1L;
    }
    else
    {
        f = n * visualize(n - 1);
        for (int j = 1; j <= i - 1; j++) cout << "|  ";
        i--;
        cout << "return " << f << " = " << n << "*factorial(" << n - 1 << ")" << endl;
        return f;
    }
}

void VisualizeFactorial()
{
    cout << "*** Visualize Factorial ***" << endl;

    unsigned long facres = visualize(5L);
    cout << "5! = " << facres << endl;
    cout << endl;
}
