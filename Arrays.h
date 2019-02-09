#pragma once

#include <iostream>
#include <string>
#include <array>

using std::cout;
using std::endl;
using std::string;

namespace ArraysExamples
{
    void DeclarationsAndInitializations()
    {
        int a1[3] = { 1, 2, 3 };
        int a2[6] = { 4, 5, 6 }; // the remaining 3 elements initialized to 0
        int a3[] = { 7, 8, 9 }; // the compiler deduces the size of the array
        int a4[10] = { 0 }; // initialize all elements to 0; this works only when initializing to zeroes
    }

    void ArraySize()
    {
        // - sizeof(int) is the same as sizeof(a1[0])
        // - std::size() returns the number of elements (C++17)
        int b[] = { 1, 2, 3, 4, 5 };
        cout << sizeof(b) / sizeof(int) << " "; // 5; this method of determining the array size is applicable only to locally allocated arrays
        cout << std::size(b) << " "; // 5
    }

    // std::array
    // - a container defined in the <array> header file
    // - a replacement for the C-style arrays
    // - always knows its size
    // - does not automatically get cast to a pointer
    // - has iterators to loop over the elements
    // - it can work with the STL algorithms
    // - has a fixed size which should be known at compile time
    void StdArray()
    {
        std::array<int, 3> arr = { 1, 2, 3 };
        cout << arr.size() << " "; // 3
    }

    // A function template that accepts arrays of variable sizes.
    template <int n>
    int Sum(std::array<int, n> values)
    {
        int res = 0;
        for (int val : values)
            res += val;
        return res;
    }

    void StdArraySum()
    {
        std::array<int, 5> numbers1 = { { 1, 2, 3, 4, 5 } }; // 15
        std::array<int, 3> numbers2 = { { 1, 3, 5 } }; // 9
        cout << Sum(numbers1) << " " << Sum(numbers2) << " ";
    }

    // std::count
    void StdCount()
    {
        // Count how many 3s are in a sub-array.
        // &c[9] is an element located one-beyond the range.
        int c[] = { 1,3,3,4,3,3,7,3,3,   3,2,3,5,4,2,3,4,2 };
        cout << std::count(&c[0], &c[9], 3) << " "; // there are six 3s in the subarray c[0..8]
    }

    // Multi-dimensional arrays
    void MultiDimensionalArrays()
    {
        // Array[how_many_elements][the_length_of_element]
        int d[3][6]; // 3 elements each the length of 6

        // C++ defines arrays in row major order which puts members of the right-most index next 
        // to each other in memory e.g. d[0][0] and d[0][1] are stored in adjacent memory locations.
        // Accessing an array in the wrong order degrades performance significantly.

        // Row major order - fast.
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 6; ++j)
                d[i][j] = 1;

        // Column major order - slow.
        for (int j = 0; j < 6; ++j)
            for (int i = 0; i < 3; ++i)
                d[i][j] = 1;

        // Initialize a multidimensional array.
        int e[2][2]{ { 1, 0 }, { 0, 1 } };

        // Modify a multidimensional array.
        e[0][1] = 8;
    }

    void CStyleArrays()
    {
        // Create and initialize an array locally.
        int a[3];
        a[0] = 0;
        a[1] = 1;
        *(a + 2) = 2; // initialize an element of an array using the pointer notation
        int a_size = sizeof(a) / sizeof(a[0]); // the number of elements in a

        // Create and initialze an array using an initializer list.
        float b[] = { 1.0,2.0,3.0 };

        // Allocate an array on the free store.
        int* c = new int[4];
        c[0] = 0;
        c[1] = 1;
        c[2] = 2;
        *(c + 3) = 3;
        int c_size = sizeof(c) / sizeof(c[0]); // c_size does NOT include the number of elements in c because sizeof(c) returns the pointer size, not the total byte size of the array
        // ...
        delete[] c;
    }


    void Test()
    {
        DeclarationsAndInitializations();
        ArraySize();
        StdArray();
        StdArraySum();
        StdCount();
        MultiDimensionalArrays();
        CStyleArrays();
    }
}