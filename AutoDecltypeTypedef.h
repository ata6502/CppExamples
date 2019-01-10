#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility> // declval

using std::cout;
using std::endl;
using std::string;

// Used in Auto() in Typedef()
class SomeClass { public: int someMemberFunction() { return 0; } };
int someFunction(int n) { return 0; }

// Used in Decltype() to show a side effect.
template <int I>
struct Num
{
    static const int c = I;
    decltype(I) _member;
    Num() : _member(c) {}
};

// Used in Decltype()
class A { private: A(); };

//
// auto and decltype provide type deduction (aka type inference)
//

void Auto()
{
    //
    // auto
    //
    // - used for deducing a type of an object from its initializer
    // - good for storing lambda expressions
    // - prefer using the assignment syntax to initializing an auto variable
    //   because a type may have an explicit copy ctor. In such a case you
    //   can only use the copy initialization:
    //   int i = 10;
    //   auto a = i; // rather than auto a(i);
    // - don't use auto when type conversion is required
    
    // All the variables are of the same type.
    auto a = 5.0, b = 10.0;
    auto c = 1.0, *ptra = &a, &refb = b;
    auto d = a; // assignment; preferred to copy initialization unless the type has an explicit copy ctor
    auto e(a); // copy initialization; use it when the type has an explicit copy ctor

    std::map<string, int> indices;
    auto& ref_indices = indices;
    auto* ptr_indices = &indices;
    const auto const_indices = indices;
    const auto& const_ref_indices = indices;

    // The const specifier is removed.
    const std::vector<int> values;
    auto v1 = values; // const is removed; the type is vector<int>
    auto& v2 = values; // the type is const vector<int>&

    // The volatile specifier is removed.
    volatile long clock = 0L;
    auto c1 = clock; // c1 is not volatile anymore

    // Arrays are turned into pointers.
    SomeClass items[10];
    auto b1 = items; // b1 is of type SomeClass*
    auto& b2 = items; // b2 is of type SomeClass(&)[10] - a reference to the array

    // If you need a reference, specify that explicitly.
    auto g = someFunction; // g is int(*)(int)
    auto& h = someFunction; // h is int(&)(int)

    // without auto
    std::vector<int> v3;
    for (std::vector<int>::iterator p = v3.begin(); p != v3.end(); ++p)
        *p = 1;

    // with auto
    std::vector<int> v4;
    for (auto p = v4.begin(); p != v4.end(); ++p)
        *p = 1;
}

void Decltype()
{
    //
    // decltype
    //
    // - used to infer the type of an expression

    int i = 7;
    cout << typeid(decltype(i + 1.0)).name() << " "; // double

    // decltype may be used in place of type anywhere.
    std::vector<int> a;
    decltype(a) b; // use decltype(a) instead of vector<int>
    b.push_back(10);
    decltype(a)::iterator iter = a.end();

    // decltype side effect:
    // The comma operator returns the last argument so var will be the same type as ii.
    // However the compiler still needs to instantiate the Num template to make sure
    // the expression is valid. This template instantiation is a side effect.
    int ii;
    decltype(Num<1>::c, ii) var = ii;

    // The expression passed to decltype has to be valid. For example, when a class has a 
    // private ctor, the following expression won't compile because A() is private:
    // typeid(decltype(A())).name()
    // In such situations, we can use the declval template:
    cout << typeid(decltype(std::declval<A>())).name() << " "; // a value reference to A: class A

    // decltype is useful when you want to deduce a type without defining an initialized variable.
    // It's used in generic programming. The following example shows the usage of dectype but most
    // likely you won't use it in this context.
    decltype(i) j = 8; // j is of type int
}

void Typedef()
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
    PFUN action;
    action = someFunction;

    // a function pointer type MFUN that points to a member function of a class MyClass
    typedef int (SomeClass::* MFUN) ();
    SomeClass obj;
    MFUN action2;
    action2 = &SomeClass::someMemberFunction;
    int n = (obj.*action2)(); // deference the function pointer
}

// Using auto with a template.
template<typename X, typename Y>
void DoWork(const X& x, const Y& y)
{
    // It would be difficult to specify the type of the result explicitly.
    auto result = x * y;
}

// Using auto and decltype.
// The return type of a function template is determined by its template arguments
template<typename X, typename Y>
auto Multiply(X x, Y y) -> decltype(x * y) // trailing return type; note that it is *after* the paramter list; thanks to that we can use x and y
{
    return x * y;
}
