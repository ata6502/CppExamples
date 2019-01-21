#pragma once

#include <iostream>

using std::cout;
using std::endl;

/*
    - Always initialize pointers to nullptr.
    - If a pointer is declared as const, the type it points to should also be declared as const.
    - Be suspicious of non-const refrence arguments; if you want the function to modify its arguments, use pointers and returned value instead.
    - A reference is a synonym of a variable or of an operation.
    - Use references instead of pointers if you can, especially as function parameters (except the incr example below)
*/

namespace PointersAndReferencesExamples
{
    class Book { };

    void Basics()
    {
        // a pointer to a character
        int a = 1;
        int *pa = &a;

        // a reference
        int b = 2;
        int &rb = b; // rb is a reference to b; changing rb, changes b

        // increment an int value in a pointer
        ++(*pa);
        cout << *pa << " "; // 2

        // increment an int value in a reference
        ++rb;
        cout << rb << " "; // 3

        // auto with references and pointers
        auto c = 3;
        auto* pc = &c;
        auto& rc = c;
        *pc = 4;
        rc = 5;
    }

    void ConstPointers()
    {
        char s[] = "test";

        char *p1 = s;               // non-const pointer, non-const data
        const char *p2 = s;         // non-const pointer, const data (a pointer to a constant)
        char const *p3 = s;         // j.w.
        char * const p4 = s;        // const pointer, non-const data 
        const char * const p5 = s;  // const pointer, const data

        const int a = 1;            // const data
        const int *pa1 = &a;        // non-const pointer to const data
        const int * const pa2 = &a; // const pointer to const data
        //int * const pa3 = &a;       // const pointer to non-const data - illegal, because the data 'a' is const

        int b = 1;
        int * const pb = &b;        // const pointer to non-const data
    }

    void PointerDeclarations()
    {
        // a reference to a pointer
        int i = 1;
        int *pi = &i;
        int &ri = *pi;
        cout << ri << " ";

        // a pointer to a reference is illegal
        // it means that storing references in a container is impossible
        // without using helper classes such as std::reference_wrapper

        // create a pointer and initialize it to null
        Book *book = nullptr;

        // a pointer to a pointer to a character
        char c = 'a';
        char *pc = &c;
        char **ppc = &pc;

        // initialize two ponters in one line
        int *x, *y; // not int* x, y

        // a pointer to an array
        int a[5] = { 1,2,3,4,5 };
        int *pa1 = a;
        int *pa2 = &a[0];

        // an array of pointers to const objects; *ps[0] = "xxx" causes a compile-time error
        // you can omit the 'const' keyword; it is allowed by the compiler for backward compatibility
        char const *ps1[] = { "aaa", "bbb", "ccc" };

        // an array of const pointers to const objects
        // *const is "constant pointer declarator" - there is no const* declarator
        // that's why "const char*" and "char const *" are equivalent
        const char * const ps2[] = { "ddd", "eee", "fff" };
        char const * const ps3[] = { "ddd", "eee", "fff" }; // the same as ps2

        // a reference to an array of 5 integers
        int b[5] = { 1,2,3,4,5 };
        int(&br)[5] = b;

        // dereference an operation (?:), rather than a single variable
        int m = 1;
        int n = 8;
        int *pm = &(m > n ? m : n);
        cout << *pm << " ";

        // implicit conversion int --> double using a temporary behind-the-scene variable
        // double& cdr = 1; would not compile
        const double &cdr = 1;
    }

    // Be suspicious of non-const refrence arguments; if you want the function to modify its arguments, use pointers and returned value instead.
    
    // incr1 has better implementation than incr2 because it accepts a pointer as a parameter. 
    void incr1(int *p)
    {
        (*p)++; // OK - enforces the calling code to pass a reference
    }

    void incr2(int &p)
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
        Basics();
        ConstPointers();
        PointerDeclarations();
        incr();
    }
}