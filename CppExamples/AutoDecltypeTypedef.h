#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace AutoDecltypeExamples
{
    // auto infers the type of an object from its initializer.
    void InitAuto()
    {
        // Multiple declarations with a single auto keyword.
        auto a = 1.0, b = 2.0, c{ 3.0 };
        auto d = 1.0, *ptra = &a, &refb = b;

        // Prefer assignment to copy initialization unless the type has an explicit copy ctor.
        auto e = a; 

        // Use copy initialization when the type has an explicit copy ctor.
        auto f(a); 

        // auto with modifiers.
        vector<int> nums = { 1,2,3 };
        auto& ref_nums = nums;
        auto* ptr_nums = &nums;
        const auto const_nums = nums;
        const auto& const_ref_nums = nums;
    }

    void RemoveQualifiers()
    {
        // Remove the const-qualification.
        const vector<int> values;
        auto a = values; // const is removed; type of a is vector<int>
        auto& b = values; // type of b is const vector<int>&

        // Remove the volatile qualifier.
        volatile long clock = 0L;
        auto c = clock; // c is not volatile anymore
    }

    class Book { };

    int func(double) { return 1; }

    void DecayToPointers()
    {
        // Decay an array into a pointer.
        Book books[10];
        auto a = books; // type of a is Book*
        auto& b = books; // type of b Book(&)[10] - a reference to the array

        // Decay a function into a pointer.
        auto c = func; // type of c is int(*)(double)
        auto& d = func; // type of d is int(&)(double)
    }

    void IterateWithAuto()
    {
        vector<int> v{ 1,2,3 };

        // without auto
        for (std::vector<int>::iterator it = begin(v); it != end(v); ++it)
            *it = 1;

        // using auto
        for (auto it = begin(v); it != end(v); ++it)
            *it = 2;
    }

    // auto with a template.
    template<typename X, typename Y>
    void DoWork(const X& x, const Y& y)
    {
        // It would be difficult to specify the type of the result explicitly.
        auto result = x * y;
    }

    // auto with decltype.
    // The return type of a function template is determined by its template arguments.
    // This template has the trailing return type declared *after* the parameter list.
    // Thanks to that we can use x and y in decltype.
    template<typename X, typename Y>
    auto Multiply(X x, Y y) -> decltype(x * y) 
    {
        return x * y;
    }

    // auto as the funtion return type.
    auto Add1(int a, int b)
    {
        return a + b;
    }

    // Tell the compiler that we return a value of the returned expression's type.
    auto Add2(int a, int b) -> decltype(auto)
    {
        return a + b;
    }

    // The same as Add2.
    decltype(auto) Add3(int a, int b)
    {
        return a + b;
    }

    auto Identity(int& x) -> decltype(auto) { return x; } // returns a reference to int

    // decltype(auto) preserves reference-ness
    void PreserveReferenceness()
    {
        int i = 1;
        Identity(i) = 2; // ok - no compiler error
    }

    void Test()
    {
        InitAuto();
        RemoveQualifiers();
        DecayToPointers();
        IterateWithAuto();
        PreserveReferenceness();
    }
}

//
// typedef
//
namespace TypedefExamples
{
    class SomeClass { public: int SomeMemberFunction() { return 0; } };
    int SomeFunction(int n) { return 0; }

    void Test()
    {
        typedef unsigned char uchar;            // unsigned char
        typedef const unsigned char cuchar;     // const unsigned char 
        typedef int* pi;                        // pointer to int
        typedef char** ppc;                     // pointer to pointer to char
        typedef int* array_ptr_int[7];          // an array of 7 pointers to int
        typedef int* (*ptr_array_ptr_int)[7];   // a pointer to an array of 7 pointers to int
        typedef int* array_array_ptr_int[2][3]; // an array of 2 arrays of 3 pointers to int
        typedef double array_double[];          // an array of double (any size)

        // a function pointer type PFUN that points to a global function that accepts an int and returns an int
        typedef int(*PFUN) (int n);
        PFUN action1;
        action1 = SomeFunction; // note that we don't use the & operator to get the address of the function SomeFunction

        // a function pointer type MFUN that points to a member function of a class SomeClass
        typedef int (SomeClass::* MFUN) ();
        SomeClass obj;
        MFUN action2;
        action2 = &SomeClass::SomeMemberFunction; // set the value of the function pointer
        int n = (obj.*action2)(); // deference the function pointer
    }
}