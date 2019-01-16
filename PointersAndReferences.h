#pragma once

#include <iostream>

using std::cout;
using std::endl;

/*
    - Always initialize pointers to nullptr.
    - If a pointer is declared as const, the type it points to should also be declared as const.
    - Be suspicious of non-const refrence arguments; if you want the function to modify its arguments, use pointers and returned value instead.
    - A reference is a synonym of a variable or of an operation.
*/
namespace PointersAndReferencesExamples
{
    void PointerDeclarations()
    {
        char s[] = "test";

        char * p1 = s;               // non-const pointer, non-const data
        const char * p2 = s;         // non-const pointer, const data (a pointer to a constant)
        char const * p3 = s;         // j.w.
        char * const p4 = s;         // const pointer, non-const data 
        const char * const p5 = s;   // const pointer, const data

        // a pointer to a character
        char c = 'a';
        char * pc = &c;

        // a pointer to a pointer to a character
        char** ppc = &pc;

        // a pointer to an array
        int a[5] = { 1,2,3,4,5 };
        int * pa1 = a;
        int * pa2 = &a[0];

        // an array of pointers to const objects; *ps[0] = "xxx" causes a compile-time error
        // you can omit the 'const' keyword; it is allowed by the compiler for backward compatibility
        char const * ps1[] = { "aaa", "bbb", "ccc" };

        // an array of const pointers to const objects
        // *const is "constant pointer declarator" - there is no const* declarator
        // that's why "const char*" and "char const *" are equivalent
        const char * const ps2[] = { "ddd", "eee", "fff" };
        char const * const ps3[] = { "ddd", "eee", "fff" }; // the same as ps2

        // a reference to an array of 5 integers
        int b[5] = { 1,2,3,4,5 };
        int(&r)[5] = b;

        // a pointer to an int
        int t = 1;
        int * pt = &t;

        // increment the int value
        ++(*pt);
        cout << *pt << " ";

        // increment the pointer
        cout << pt << " ";
        ++pt;
        cout << pt << " ";

        // a pointer to a const int
        const int d = 1;
        const int * pd = &d;

        // const pointer to an integer
        int i = 1;
        int * const pi = &i;

        // dereference an operation (?:), rather than a single variable
        int m = 1;
        int n = 8;
        int * pm = &(m > n ? m : n);
        cout << * pm << " ";

        // implicit conversion int --> double using a temporary behind-the-scene variable
        // double& cdr = 1; would not compile
        const double& cdr = 1;
    }

    // Be suspicious of non-const refrence arguments; if you want the function to modify its arguments, use pointers and returned value instead.
    
    // incr1 has better implementation than incr2 because it accepts a pointer as a parameter. 
    void incr1(int * p)
    {
        (*p)++; // OK - enforces the calling code to pass a reference
    }

    void incr2(int& p)
    {
        p++; // BAD - modifies the argument without informing a user
    }

    void incr()
    {
        int c = 0;
        incr1(&c);  // you know c will be modified
        cout << c << " ";
        incr2(c);   // you do not know that c will be modified
        cout << c << " ";
    }

    void PointersAndReferences()
    {
        PointerDeclarations();
        incr();
    }
}