#pragma once

#include <iostream>
#include <stdexcept> // exception classes: exception, invalid_argument, out_of_range, etc.
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
    Good practice:
    - *** Catch exceptions by reference ***. Otherwise, slicing may occur. This applies to the exceptions that are in the exception hierarchy.
    - Catch more specific exceptions first. For example, catch std::out_of_range before catching std::exception.

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
*/

namespace ExceptionsExamples
{
    class Book { };

    void Exceptions()
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


        // When you use RAII pattern such as smart pointers, there is no need 
        // for the finally block.The reason is that the pointers are allocated 
        // on a stack and deallocated when control is transferred to the catch block.
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