#pragma once

#include <iostream>
#include <iomanip> // setiosflags, setprecision

using std::cout;
using std::endl;

/*
    In C++ the template arguments don't have to be type names. 
    They can be variable names, function names, and constant 
    expressions as well.

    Variadic templates allow templates to take an arbitrary 
    number of type parameters.

    Local and unnamed types can be used as template arguments.
*/

// Function templates

template<typename T>
T Min(const T& a, const T& b)
{
    return (a < b ? a : b);
}

template <class T>
T Max(const T& a, const T& b)
{
    return (a > b ? a : b);
}

template <class T>
void Print(T a[], unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
        cout << a[i];
}


// Class templates

template <class T>
class Accumulator
{
public:
    Accumulator(T start) : m_total(start) {};
    T operator+=(const T& t) { return m_total += t; };
    T GetTotal() { return m_total; }
private:
    T m_total;
};


// Tests

void AccumulatorTest()
{
    Accumulator<int> accum(0); // always specify a type for class templates
    accum += 3;
    accum += 7;
    cout << accum.GetTotal() << " ";

    Accumulator<string> accum2("");
    accum2 += "hello";
    accum2 += " world";
    cout << accum2.GetTotal() << " ";
}

void MinMaxTest()
{
    int a = 2, b = 8;
    cout << "min=" << Min(a, b) << " "; // the compiler figures out what type you want to use; the same as Min<double>(a,b)
    cout << "max=" << Max(a, b) << " ";

    char x = 'e', y = 'c';
    cout << "min=" << Min(x, y) << " ";
    cout << "max=" << Max(x, y) << " ";

    double f1 = 3.4, f2 = 2.6;
    cout << "min=" << std::setiosflags(std::ios::fixed) << std::setprecision(3) << Min(f1, f2) << " ";
    cout << "max=" << std::setiosflags(std::ios::fixed) << std::setprecision(3) << Max(f1, f2) << " ";
}


namespace TemplatesExamples
{
    void Templates()
    {
        AccumulatorTest();
        MinMaxTest();
    }
}
