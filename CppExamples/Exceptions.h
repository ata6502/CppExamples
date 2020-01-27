#pragma once

#include <iostream>
#include <stdexcept> // exception classes: exception, invalid_argument, out_of_range, etc.
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
    Common exception-derived classes. They differ only by their names:
    - logic_error
        - invalid_argument
        - domain_error
        - out_of_range
        - length_error
    - runtime_error
        - overflow_error
        - range_error
        - underflow_error

    noexcept specification:
    - noexcept and noexcept(true) mean "this does not throw"
    - noexcept(false) means "this might throw"
    - not checked at compile time
    - enables faster code, for example a function std::move_if_noexcept() may use it
    - a rule of thumb: mark code as noexcept and remove it when it's not true
    - when code is marked as noexcept but throws an exception, the application is aborted
*/

namespace ExceptionsExamples
{
    class Book { };

    void Test()
    {
        // Throw and catch an exception.
        try
        {
            throw std::invalid_argument("An error occurred");
        }
        catch (std::exception& exc)
        {
            cout << exc.what() << " ";
        }


        // It's better to catch a specific exception.
        try
        {
            vector<int> v;
            v.push_back(1);

            int i = v.at(10);
        }
        catch (std::out_of_range& exc)
        {
            cout << exc.what() << " ";
        }


        // Use the RAII pattern such as smart pointers. We don't need explicitly to
        // release any resources because the smart pointer is allocated on a stack 
        // and deallocated when control is transferred to the catch block.
        try
        {
            auto x = std::make_shared<Book>(); // allocation
            // ...
            throw std::domain_error("error");

        }
        catch (std::exception&)
        {
            cout << "deallocation ";
        }
    }
}