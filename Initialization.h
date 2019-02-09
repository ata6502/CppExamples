#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <initializer_list> // std::initializer_list

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::complex;

namespace InitializationExamples
{
    void UniformInitialization()
    {
        // Examples of uniform initialization.
        int values[]{ 1, 2, 3 };
        vector<int> v{ 2, 3, 5, 7, 11, 13, 17 };
        vector<string> cities{ "Berlin", "New York", "London", "Toronto", "Cairo", "Warsaw" };
        complex<double> c{ 4.0, 3.0 }; // equivalent to c(4.0,3.0)
    }

    void ValueInitialization()
    {
        // An initializer list forces value initialization: even local variables 
        // of fundamental data types are initialized to zero or nullptr.
        int j{};    // j is initialized by 0
        int* q{};   // q is initialized by nullptr

#pragma warning(push)
#pragma warning(disable : 4101)
        int i;      // i has undefined value
        int* p;     // p has undefined value
#pragma warning(pop)
    }

    void NarrowingInitialization()
    {
        // Narrowing initializations are the initializations that reduce precision or 
        // where the supplied value gets modified.
        // Narrowing initializations are not possible with uniform initialization.
#pragma warning(push)
#pragma warning(disable : 4244)
        int x1(5.3);        // OK, but x1 becomes 5
        int x2 = 5.3;       // OK, but x2 becomes 5
#pragma warning(pop)
        //int x3{ 5.0 };    // ERROR: narrowing
        //int x4 = { 5.3 }; // ERROR: narrowing
        char c1{ 7 };       // OK: even though 7 is an int, this is not narrowing; if a value can be represented exactly as the target type, the conversion is not narrowing
        //char c2{ 99999 }; // ERROR: narrowing (if 99999 doesn't fit into a char)
        std::vector<int> v1{ 1, 2, 4, 5 }; // OK
        //std::vector<int> v2{ 1, 2.3, 4, 5.6 }; // ERROR: narrowing doubles to ints
    }

    // Used in PassInitializerList()
    void print(std::initializer_list<int> vals)
    {
        for (auto p = vals.begin(); p != vals.end(); ++p)
        {
            cout << *p;
        }
        cout << " ";
    }

    void InitializerListAsFunctionArgument()
    {
        // Pass a list of values to a function.
        print({ 3,2,1 });
    }

    // A class with two constructors:
    // - one ctor for a specific number of arguments 
    // - another ctor for an initializer list
    // the version with the initializer list is preferred
    class P
    {
    public:
        P(int, int) {};
        P(std::initializer_list<int>) {};
    };

    // Because of initializer lists, explicit becomes relevant for constructors taking more
    // than one argument. You can disable automatic type conversions from multiple values, 
    // which is also used when an initialization uses the = syntax.
    class R
    {
    public:
        R(int a, int b) {};
        explicit R(int a, int b, int c) {};
    };

    void fr(const R&) {}

    // The class template std::initializer_list<> supports the concept of *initializer lists* 
    // for user-defined types.
    void InitializerListAndUserDefinedTypes()
    {
        // The version with the initializer list is preferred.
        P p1(77, 5);       // calls P::P(int,int)
        P p2{ 77,5 };      // calls P::P(initializer_list)
        P p3{ 77,5,42 };   // calls P::P(initializer_list)
        P p4 = { 77,5 };   // calls P::P(initializer_list)

        // Disable automatic type conversions.
        R r1(77, 5); // OK
        R r2{ 77,5 }; // OK
        R r3{ 77,5,42 }; // OK
        R r4 = { 77,5 }; // OK (implicit type conversion allowed)
        //R r5 = { 77,5,42 }; // ERROR due to explicit (no implicit type conversion allowed)

        fr({ 47,11 }); // OK, implicit conversion of {47,11} into R
        //fr({ 47,11,3 }); // ERROR due to explicit
        fr(R{ 47,11 }); // OK, explicit conversion of {47,11} into R
        fr(R{ 47,11,3 }); // OK, explicit conversion of {47,11,3} into R
    }

    void Initialization()
    {
        UniformInitialization();
        ValueInitialization();
        NarrowingInitialization();
        InitializerListAsFunctionArgument();
        InitializerListAndUserDefinedTypes();
    }
}