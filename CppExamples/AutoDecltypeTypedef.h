#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility> // declval

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

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
namespace AutoExamples
{
    class Book
    {
    public:
        Book() : m_title(string()) {}
        Book(const string& title) : m_title(title) {}
        string GetTitle() const { return m_title; }
    private:
        string m_title;
    };

    int func(double) { return 10; }

    void InitAuto()
    {
        // Multiple declarations with a single auto keyword.
        auto a = 1.0, b = 2.0, c{ 3.0 };
        auto d = 1.0, *ptra = &a, &refb = b;
        auto e = a; // assignment; preferred to copy initialization unless the type has an explicit copy ctor
        auto f(a); // copy initialization; use it when the type has an explicit copy ctor

        // Initialize an object.
        auto book = Book("A");
        cout << book.GetTitle() << " ";

        // Add modifiers to auto.
        map<string, int> indices;
        auto& ref_indices = indices;
        auto* ptr_indices = &indices;
        const auto const_indices = indices;
        const auto& const_ref_indices = indices;
    }

    void RemoveSpecifiers()
    {
        // Remove the const specifier.
        const vector<int> values;
        auto a = values; // const is removed; type of a is vector<int>
        auto& b = values; // type of b is const vector<int>&

        // Remove the volatile specifier.
        volatile long clock = 0L;
        auto c = clock; // c is not volatile anymore
    }

    void DecayArraysAndFunctionsToPointers()
    {
        // Turn an array into a pointer.
        Book books[10];
        auto a = books; // type of a is Book*
        auto& b = books; // type of b Book(&)[10] - a reference to the array

        // Turn a function into a pointer.
        auto c = func; // type of c is int(*)(double)
        auto& d = func; // type of d is int(&)(double)
    }

    void IterateWithAuto()
    {
        vector<int> v{ 1,2,3 };

        // without auto
        for (std::vector<int>::iterator it = begin(v); it != end(v); ++it)
            *it = 1;

        // with auto
        for (auto it = begin(v); it != end(v); ++it)
            *it = 2;
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

    void Test()
    {
        InitAuto();
        RemoveSpecifiers();
        DecayArraysAndFunctionsToPointers();
        IterateWithAuto();
    }
}

//
// decltype
//
// - used to infer the type of an expression
namespace DecltypeExamples
{
    // A template for SideEffect.
    template <int I>
    struct Num
    {
        static const int c = I;
        decltype(I) _member;
        Num() : _member(c) {}
    };

    void GetTypeOfExpression()
    {
        int i = 10;
        cout << typeid(decltype(i + 1.0)).name() << " "; // double

        // decltype may be used in place of type.
        vector<int> a;
        decltype(a) b; // decltype(a) instead of vector<int>
        b.push_back(10);
        decltype(a)::iterator it = a.end();
    }

    void SideEffect()
    {
        // The comma operator returns the last argument. It means that var is the same type as i.
        // However, the compiler still needs to instantiate the Num template to make sure 
        // the expression is valid. The template instantiation is a side effect.
        int i;
        decltype(Num<1>::c, i) var = i;
    }

    class A { private: A(); };

    void DeclvalExample()
    {
        // The expression passed to decltype has to be valid. For example, when a class has a 
        // private ctor, the following expression doesn't compile because A() is private:
        // typeid(decltype(A())).name()
        // In such situations, we can use the declval template:
        cout << typeid(decltype(std::declval<A>())).name() << " "; // output: class DecltypeExamples::A

        // decltype is useful when you want to deduce a type without defining an initialized variable.
        // It's used in generic programming. The following example shows the usage of dectype but most
        // likely you won't use it in this context.
        int i = 1;
        decltype(i) j = 8; // j is of type int
    }

    void Test()
    {
        GetTypeOfExpression();
        SideEffect();
        DeclvalExample();
    }
}

//
// typedef
//
namespace TypedefExamples
{

    class SomeClass { public: int someMemberFunction() { return 0; } };
    int someFunction(int n) { return 0; }

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
        PFUN action;
        action = someFunction; // note that we don't use the & operator to get the address of the function someFunction

        // a function pointer type MFUN that points to a member function of a class SomeClass
        typedef int (SomeClass::* MFUN) ();
        SomeClass obj;
        MFUN action2;
        action2 = &SomeClass::someMemberFunction; // set the value of the function pointer
        int n = (obj.*action2)(); // deference the function pointer
    }
}