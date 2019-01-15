#pragma once

#include <iostream>
#include <string>
#include <sstream>  // ostringstream, istringstream
#include <iomanip>  // setiosflags, setprecision

using std::cout;
using std::endl;
using std::string;

// <cstdlib> contains conversion functions for numbers to text and text to numbers.
// The following two functions (CovertDoubleToString and ConvertStringToDouble) do not
// use functions from <cstdlib>.

string CovertDoubleToString(double n)
{
    std::ostringstream ostr;
    ostr << n;

    return ostr.str();
}

double ConvertStringToDouble(string s)
{
    double n;
    std::istringstream istr(s);
    istr >> n;
    if (istr.fail() || !istr.eof())
        return 0;

    return n;
}

namespace ConversionExamples
{
    void Conversion()
    {
        cout << CovertDoubleToString(273.1458) << " ";                         // 273.146
        cout << ConvertStringToDouble("273.1458") << " ";                      // 273.15
        cout << std::setprecision(4) << ConvertStringToDouble("273.1458") << " ";   // 273.1458
    }
}