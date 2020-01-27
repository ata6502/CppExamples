#pragma once

#include <windows.h>
#include <crtdbg.h> // Microsoft's implementation of CRT; contains _ASSERTE
//#include <cassert> // contains the C-style assert macro; good for console apps
#include <iostream>

using std::cout;
using std::endl;

namespace Diagnostics
{
    //
    // Assertions
    //
    // Run-time assertion. ASSERT is evaluated only in Debug builds.
    #define ASSERT _ASSERTE

    // Compile-time assertion. It can be place inside or outside
    // of a function.
    static_assert(sizeof(float) == 4, "can't serialize floats!");

    void TestAssert()
    {
        // ASSERT(4 == 5); // uncomment to demonstrate assertion fail
    }


    //
    // Verify
    //
    // Verify behaves exactly the same as Assert in Debug builds.
    // In Release builds, Verify drops the verification but keeps
    // the expression. It is useful when the expression is essential 
    // to the application operation and cannot be stripped out in 
    // Release builds.

    // Verify is used with functions that return a bool value.
    // This is useful in a destructor where it wouldn't be safe 
    // to throw an exception. Instead, we check the validity of 
    // an operation in Debug builds. 
    // ~Owner()
    // {
    //     VERIFY(CloseHandle(handle));
    // }

    // Define VERIFY as an assertion in Debug builds.
    // In other builds, define VERIFY as the expression itself.
    #ifdef _DEBUG
    #define VERIFY ASSERT
    #else
    #define VERIFY(expression) (expression)
    #endif

    // The Windows operating system provides a lightweight event kernel object that is useful for signalling and synchronization. 
    // It is a part of the core Windows API and it is exposed through a C-style API. It comes in two varieties: ManualResetEvent or 
    // AutoResetEvent object. We create a ManualResetEvent here.
    
    // An exception class thrown when the CreateEvent function fails i.e., retuns a null pointer.
    struct LastException
    {
        DWORD result; // holds an error code

        // A ctor calling the Window's GetLastError function.
        // The GetLastError function is called to get a specific 
        // error code describing the failure. 
        LastException() : result{ GetLastError() } {}
    };

    // A simple wrapper around the ResetEvent kernel object.
    struct ManualResetEvent
    {
        HANDLE m_handle; // holds the event handle

        // A default constructor to create the event object.
        ManualResetEvent()
        {
            // Create the ManualResetEvent object. It is possible that the CreateEvent
            // function fails.
            m_handle = CreateEvent(
                nullptr,   // use the default security descriptor
                true,      // true requests a ManualResetEvent object as opposed to an AutoResetEvent
                false,     // false means that the object should be initially non-signaled
                nullptr);  // the name of the event (none)

            // If the CreateEvent function fails, it returns a null pointer.
            if (!m_handle)
            {
                throw LastException();
            }
        }

        ~ManualResetEvent()
        {
            // Close the event handle.
            // The kernel object handle represents a kind of reference count and it's our job 
            // to call the CloseHandle function. The CloseHandle function returns a Boolean value 
            // indicating success or failure. 
            VERIFY(CloseHandle(m_handle));
        }
    };

    void TestVerify()
    {
        auto e1 = ManualResetEvent{};

        // Copy the event object using the default copy ctor created by the compiler. 
        // The default copy ctor copies the event handle. 
        // When e1 is destructed, the handle is closed and Verify does not show any errors.
        // When e2 is destructed, we attempt to call the CloseHandle function with an invalid handle. 
        //auto e2 = e1; // uncomment to throw the "invalid handle" exception

        // Debug build:
        // - Under the debugger: CloseHandle knows it is running under a debugger and throws an exception "An invalid handle was specified".
        // - Without debugging: the Verify macro is turned into an assertion.
        // Release build:
        // - Under the debugger: the same as in the Debug build - CloseHandle knows it is running under a debugger and throws an exception "An invalid handle was specified".
        // - Without debugging: the application runs without any visible errors although CloseHandle is still being called and the redundant call is still failing.
    }



    //
    // TRACE
    //
    #include <stdio.h> // printf variants provided by CRT
    
    // OutputDebugString - Windows provides the debugging hooks that Visual Studio relies on
    // This also has the benefit of allowing you to watch Trace output in something other than Visual Studio.
    // The OutputDebugString function can send a string to the debugger for display, but it doesn't support formatting. 

    #ifdef _DEBUG

    // The C-like Trace function:
    // - Sends output to the debugger for display.
    // - Accepts a variable number of arbitrarily typed arguments. This is the C-style approach.
    // - Relies on macros and compiler internals to unpack the arguments.
    inline void Trace(wchar_t const * format, ...)
    {
        va_list args;
        va_start(args, format); // initialize the arguments list (va_list) with the name of the last formal argument, in this case 'format'

        // The output buffer for printf.
        wchar_t buffer[256];

        // There are more macros to pick individual arguments in order. In this case, however, 
        // we just use a printf variant that takes the argument list and print the formatted 
        // output to a local buffer. 
        // _vsnwprintf_s is a VC++ CRT version (a function template) of printf with security enhancements.
        // It determines the buffer size from the first argument.
        // The printf function returns -1 on failure.
        ASSERT(-1 != _vsnwprintf_s(
            buffer, 
            _countof(buffer) - 1, // limits the output to buffer count -1 to accommodate the null terminator
            format,
            args));

        va_end(args); // clean up the stack

        // Pass the formatted string to any listening debugger.
        OutputDebugString(buffer);
    }

    // The variadic template Trace function - a type safe alternative to the C-like mechanism.
    struct Tracer
    {
        char const * m_filename;
        unsigned m_line;

        // The Tracer ctor accepts two arguments: the file name and the line number.
        Tracer(char const * filename, unsigned const line) :
            m_filename{ filename },
            m_line{ line }
        { }

        // The function call operator (the function object) arguments:
        // - the format string 
        // - the variable number of arguments; the Args argument is a parameter pack
        template <typename... Args>
        void operator()(wchar_t const * format, Args... args) const
        {
            wchar_t buffer[256];

            // We need to create a preamble (the filename and the line number) and the formatted string 
            // and then combine them.
             
            // First, populate the buffer with the filename and line number.
            // Also, obtain the number of characters written to the buffer.
            // We will use it to offset the formatted output. 
            auto count = swprintf_s( // swprintf_s is a secure version of printf that prints output to a buffer rather than to the console
                buffer, 
                L"%S(%d): ",
                m_filename,
                m_line);

            // Make sure printf succeeded.
            ASSERT(-1 != count);

            // Second, add to the buffer the formatted string.
            ASSERT(-1 != _snwprintf_s(
                buffer + count, // apply the preable offset
                _countof(buffer) - count, // the limits
                _countof(buffer) - count - 1,
                format,
                args...)); // expand the parameter pack

            OutputDebugString(buffer);
        }
    };
    #endif

    // In Debug builds, we construct the Tracer object passing two arguments to its ctor.
    // In Release builds, the __noop intrinsic specifies that no code should be generated.
    #ifdef _DEBUG
    #define TRACE Diagnostics::Tracer(__FILE__, __LINE__)
    #else
    #define TRACE __noop
    #endif

    void TestTrace()
    {
        // Invoke the Tracer's function call operator (the function object) and pass
        // the format string and a list of values.
        TRACE(L"1 + 2 = %d\n", 1 + 2);
    }


    void Test()
    {
        TestAssert();
        TestVerify();
        TestTrace();
    }
}
