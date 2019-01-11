#pragma once

#include <iostream>
#include <stdexcept> // do we need it?
#include <memory> // do we need it?

using std::cout;
using std::endl;

/*
    Good practice:
    - Catch exceptions by reference. Otherwise, slicing may occur.

    Common exception-derived classes. They differ only by name:
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


        // When you use RAII pattern such as smart pointers, there is no need 
        // for the finally block.The reason is that the pointers are allocated 
        // on a stack and deallocated when control is transferred to the catch block.
        try
        {
            auto x = std::make_shared<Book>(); // allocation
            // ...
            throw std::domain_error("error");

        }
        catch (std::exception& exc)
        {
            cout << "deallocation ";
        }
    }
}