#pragma once

#include <iostream>
#include <string>
#include <array>

using std::cout;
using std::endl;
using std::string;

namespace ArraysExamples
{
    void DeclarationAndInitialization()
    {
        int a[3] = { 1, 2, 3 }; // initialize an array
        int b[6] = { 4, 5, 6 }; // initialize the remaining three elements to 0
        int c[] = { 7, 8, 9 }; // deduce the size of an array
        int d[10] = { 0 }; // initialize all elements to 0; this works only when initializing to zeroes
    }

    void ArraySize()
    {
        // - sizeof(int) is the same as sizeof(a[0])
        // - std::size() returns the number of elements (C++17)
        int a[] = { 1, 2, 3, 4, 5 };
        cout << sizeof(a) / sizeof(int) << " "; // 5; this method of determining the array size is applicable only to locally allocated arrays
        cout << std::size(a) << " "; // 5
    }

    // std::array
    // - a container defined in the <array> header file
    // - a replacement for the C-style arrays
    // - always knows its size
    // - does not automatically get cast to a pointer
    // - has iterators to loop over the elements
    // - it can work with the STL algorithms
    // - has a fixed size known at compile time
    void StdArray()
    {
        std::array<int, 3> a = { 1, 2, 3 };
        cout << a.size() << " "; // 3
    }

    // A function template that accepts std::array.
    template <int N>
    int Sum(std::array<int, N> values)
    {
        int sum = 0;
        for (int val : values)
            sum += val;
        return sum;
    }

    void StdArraySum()
    {
        std::array<int, 5> a = { { 1, 2, 3, 4, 5 } }; // 15
        std::array<int, 3> b = { { 1, 3, 5 } }; // 9
        cout << Sum(a) << " " << Sum(b) << " ";
    }

    // std::count
    void StdCount()
    {
        // Count how many 3s are in a sub-array.
        // &a[9] is an element located one-beyond the range.
        int a[] = { 1,3,3,4,3,3,7,3,3,   3,2,3,5,4,2,3,4,2 };
        cout << std::count(&a[0], &a[9], 3) << " "; // there are six 3s in the subarray a[0..8]
    }

    void MultiDimensionalArrays()
    {
        // Initialize a multidimensional array.
        int a[2][2]{ { 1, 0 }, { 0, 1 } };

        // Modify a multidimensional array.
        a[0][1] = 8;
    }

    // C++ defines arrays in row major order which puts members of the right-most index next 
    // to each other in memory e.g. a[0][0] and a[0][1] are stored in adjacent memory locations.
    // Accessing an array in the wrong order degrades performance significantly.
    void RowMajorOrderVsColumnMajorOrder()
    {
        // Array[how_many_elements][the_length_of_element]
        int a[3][6]; // 3 elements each of length 6

        // Row major order - fast.
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 6; ++j)
                a[i][j] = 1;

        // Column major order - slow.
        for (int j = 0; j < 6; ++j)
            for (int i = 0; i < 3; ++i)
                a[i][j] = 1;
    }

    void CStyleArrays()
    {
        // Create and initialize an array locally i.e. on the stack.
        int a[3];
        a[0] = 0;
        a[1] = 1;
        *(a + 2) = 2; // initialize an element of an array using the pointer notation
        int a_size = sizeof(a) / sizeof(a[0]); // the number of elements in a
        cout << a_size << " "; // 3

        // Allocate an array on the free store.
        int* b = new int[4];
        b[0] = 0;
        b[1] = 1;
        b[2] = 2;
        *(b + 3) = 3;
        int b_size = sizeof(b) / sizeof(b[0]); // b_size does NOT include the number of elements in b because sizeof(b) returns the pointer size, not the total byte size of the array
        cout << b_size << " "; // 2
        delete[] b;

        // Create and initialze an array using an initializer list.
        float c[] = { 1.0,2.0,3.0 };
    }

    void Test()
    {
        DeclarationAndInitialization();
        ArraySize();
        StdArray();
        StdArraySum();
        StdCount();
        MultiDimensionalArrays();
        RowMajorOrderVsColumnMajorOrder();
        CStyleArrays();
    }
}