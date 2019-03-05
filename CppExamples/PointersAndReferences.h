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
    void Basics()
    {
        // a pointer to a character
        int a = 1;
        int* pa = &a;

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
        // non-const data
        int i = 0, j = 9;

        // pointer to a const
        const int * p1 = &i;       // the same as: int const * p1 = &i;
        //*p1 = 1;                 // illegal - you can't modify const value
        p1 = &j;                   // ok

        // const pointer
        int * const p2 = &i;
        *p2 = 1;                   // ok
        //p2 = &j;                 // illegal - you can't modify const pointer

        // const pointer to a const
        const int * const p3 = &i;
        //*p3 = 1;                 // illegal - you can't modify const value
        //p3 = &j;                 // illegal - you can't modify const pointer

        // Note that you can modify the value of a variable the 'pointer to a const'
        // points to but you can't modify the value the pointer contains.
        j++; // modify the value of a variable the pointer points to (j)
        cout << *p1 << " ";

        //(*p1)++; // illegal - you can't modify the value the 'pointer to a const' contains

        // const data
        const int k = 1;

        // non-const pointer to a const
        const int * p4 = &k;

        // const pointer to a const
        const int * const p5 = &k; 

        // const pointer to a non-const
        //int * const p6 = &a;     // illegal - 'k' is const
    }

    class Book {};

    void PointerDeclarations()
    {
        // a reference to a pointer
        int i = 1;
        int* pi = &i;
        int& ri = *pi;
        cout << ri << " ";

        // a pointer to a reference is illegal
        // it means that storing references in a container is impossible
        // without using helper classes such as std::reference_wrapper

        // create a pointer and initialize it to null
        Book* book = nullptr;

        // a pointer to a pointer to a character
        char c = 'a';
        char* pc = &c;
        char** ppc = &pc;

#pragma warning(push)
#pragma warning(disable : 4101)
        // initialize two ponters in one line
        int *x, *y; // not int* x, y
#pragma warning(pop)

        // a pointer to an array
        int a[5] = { 1,2,3,4,5 };
        int* pa1 = a;
        int* pa2 = &a[0];

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
        int* pm = &(m > n ? m : n);
        cout << *pm << " ";

        // implicit conversion int --> double using a temporary behind-the-scene variable
        // double& cdr = 1; would not compile
        const double& cdr = 1;
    }

    // Be suspicious of non-const refrence arguments; if you want the function to modify its arguments, use pointers and returned value instead.
    
    // incr1 has better implementation than incr2 because it accepts a pointer as a parameter. 
    void incr1(int* p)
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

    // If you want to pass a reference as well as a literal to a function,
    // the function argument has to be a const reference.
    int fun(const int& x)
    {
        return x * 2;
    }



    void PointersAndReferences()
    {
        Basics();
        ConstPointers();
        PointerDeclarations();
        incr();

        int a = 3;
        fun(a);
        fun(4);
    }
}