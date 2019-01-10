#pragma once

#include <iostream>
#include <string>
#include <array>

using std::cout;
using std::endl;
using std::string;

void Arrays()
{
    //
    // Array declaration and initialization
    //
    int a1[3] = { 1, 2, 3 };
    int a2[6] = { 4, 5, 6 }; // the remaining 3 elements initialized to 0
    int a3[] = { 7, 8, 9 }; // the compiler deduces the size of the array
    int a4[10] = { 0 }; // initialize all elements to 0; this works only when initializing to zeroes

    //
    // Array size
    //
    // - sizeof(int) is the same as sizeof(a1[0])
    // - std::size() returns the number of elements (C++17)
    int b[] = { 1, 2, 3, 4, 5 };
    cout << sizeof(b) / sizeof(int) << " "; // 5
    cout << std::size(b) << " "; // 5

    //
    // std::array
    //
    // - a container defined in the <array> header file
    // - a replacement for the C-style arrays
    // - always knows its size
    // - does not automatically get cast to a pointer
    // - has iterators to loop over the elements
    // - it can work with the STL algorithms
    // - has a fixed size which should be known at compile time
    std::array<int, 3> arr = { 1, 2, 3 };
    cout << arr.size() << " "; // 3

    //
    // std::count
    //
    // Count how many 3s are in a sub-array.
    // &c[9] is an element located one-beyond the range.
    int c[] = { 1,3,3,4,3,3,7,3,3,   3,2,3,5,4,2,3,4,2 };
    cout << std::count(&c[0], &c[9], 3) << " "; // there are six 3s in the subarray c[0..8]

    //
    // Multi-dimensional arrays
    //
    // Array[how_many_elements][the_length_of_element]
    int d[3][6]; // 3 elements each the length of 6

    // C++ defines arrays in row major order which puts members of the right-most index next 
    // to each other in memory e.g. d[0][0] and d[0][1] are stored in adjacent memory locations.
    // Accessing an array in the wrong order degrades performance significantly.

    // Row major order - fast.
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 6; ++j)
            d[i][j] = 1.0f;

    // Column major order - slow.
    for (int j = 0; j < 6; ++j)
        for (int i = 0; i < 3; ++i)
            d[i][j] = 1.0f;

    //
    // Copy a char array i.e., a C-style string
    //
    char dst[20];
    char src[] = "abcdefg";
    for (int i = 0; (dst[i] = src[i]) != '\0'; i++)
        ;
    cout << dst << " ";
}
