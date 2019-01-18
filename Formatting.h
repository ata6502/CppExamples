#pragma once

#include <iostream>
#include <string>
#include <iomanip>  // setiosflags, setprecision

using std::cout;
using std::endl;
using std::string;

namespace FormattingExamples
{
    void FormatNumbers()
    {
        // Display the value 123.456789 in a field. Set the width of the field to 10 characters. 
        // Right justify the numbers in their field. Note that the numbers are automatically round up.
        cout << std::setiosflags(std::ios::fixed | std::ios::showpoint | std::ios::right)
            << std::setprecision(1) << std::setw(10) << 123.456789 // 123.5
            << std::setprecision(2) << std::setw(10) << 123.456789 // 123.45
            << std::setprecision(3) << std::setw(10) << 123.456789 // 123.457
            << " ";

        // Display the result of 4.5^5 (=1845.28125) with the precision of 2 in a field width of 10.
        cout << std::setiosflags(std::ios::fixed | std::ios::showpoint)
            << std::setprecision(2) << std::setw(10) << pow(4.5, 5.0) // 1845.28
            << " ";

        // Use std::to_string()
        double d = 2.72;
        cout << std::to_string(d) << " "; // 2.720000
    }

    // Show integer values of characters as decimal and hexadecimal numbers.
    void FormatHexAndDec()
    {
        for (int i = int('I'); i <= int('K'); ++i)
        {
            cout << "'" << char(i) << "' = " <<
                std::dec << i << "(dec)" << "/" <<
                std::hex << i << "(hex) ";
        }

        for (int i = int('7'); i <= int('9'); ++i)
        {
            cout << "'" << char(i) << "' = " <<
                std::dec << i << "(dec)" << "/" <<
                std::hex << i << "(hex) ";
        }

        // Clean up.
        cout << std::dec;
    }

    void Formatting()
    {
        FormatNumbers();
        FormatHexAndDec();
    }
}