#pragma once

/*
    - Array declaration: Array[how_many_elements][the_length_of_element]
    - C++ defines arrays in row major order. This ordering puts members of the right-most index next to each other in memory 
      e.g. test[0][0][0] and test[0][0][1] are stored in adjacent memory locations.

    Good practices:
    - Use the array notation instead of pointer notation when manipulationg arrays.
*/

// helpers
template <class T>
void Print(T a[], unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
        cout << a[i] << ' ';
    cout << endl;
}

#include <iostream>
#include <algorithm>
#include <string>
#include <array>

using std::cout;
using std::endl;
using std::string;

void ArrayInitialization()
{
    int a1[3] = { 1, 2, 3 };
    Print<int>(a1, sizeof(a1) / sizeof(int)); // sizeof(int) is the same as sizeof(a1[0])
    Print<int>(a1, std::size(a1)); // std::size() returns the number of elements (C++17)

    int a2[6] = { 4, 5, 6 }; // the remaining 3 elements initialized to 0
    Print<int>(a2, sizeof(a2) / sizeof(int));

    int a3[] = { 10, 11, 12, 13, 14 }; // the compiler deduces the size of the array
    Print<int>(a3, sizeof(a3) / sizeof(int));

    string months[12] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    Print<string>(months, 12);


    // Initialize all elements of an array to 0. This technique works 
    // only when initializing to zeroes.
    int arr[10] = { 0 };
    Print<int>(arr, sizeof(arr) / sizeof(int));

    // C-style arrays
    char c1[3] = { 'O', 'J', 0 };
    Print<char>(c1, sizeof(c1) / sizeof(char));

    char c2[] = { 'H','i',' ','t','h','e','r','e',0 };
    Print<char>(c2, sizeof(c2) / sizeof(char));

    // Initialize a C-style array of strings. Only pointers are actually stored in the array.
    char* names[3] = { "aaa", "bbb", "ccc" };
}

/*
std::array is a container defined in the <array> header file. This is a replacement for the C-style arrays.

The std::array:
- always knows its size
- does not automatically get cast to a pointer
- has iterators to loop over the elements
- it can work with the STL algorithms
- has a fixed size which should be known at compile time
*/
void StandardArray()
{
    std::array<int, 3> arr = { 1,2,3 };
    cout << "Array size = " << arr.size() << endl;
    for (auto n : arr)
        cout << n << " ";
    cout << endl;
}

struct Point { double X, Y, Z; };

// C++17
void StructuredBindings()
{
    // Structured bindings allow you to declare multiple variables that are initialized 
    // with elements from an array, struct, pair, or tuple.
    std::array<int, 3> values = { 11, 22, 33 };

    // You can declare three variables, x, y, and z, initialized with the three values 
    // from the array as follows.
    auto[a, b, c] = values;

    // The number of variables declared with the structured binding has to match the number 
    // of values in the expression on the right.

    // Structured bindings also work with structures if all non-static members are public.
    Point point;
    point.X = 1.0; point.Y = 2.0; point.Z = 3.0;
    auto[x, y, z] = point;
}

void ArrayFunctions()
{
    // Count how many 3s are in a sub-array.
    // IMPORTANT: &a[9] is an element located one-beyond the range.
    int a[] = { 1,3,3,4,5,3,7,3,2,3,2,3,5,4,2,3,4,2 };
    cout << "There are " << std::count(&a[0], &a[9], 3) << " occurrences of 3." << endl;
}

void ArrayPerformance()
{
    // C++ defines arrays in row major order. This ordering puts members of the right-most index 
    // next to each other in memory e.g.test[0][0][0] and test[0][0][1] are stored in adjacent memory locations.

    // Accessing an array in the wrong order degrades performance significantly.
    const int MAX = 50;
    float test[MAX][MAX][MAX]; // 125,000 elements

    // row major order - FAST
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            for (int k = 0; k < MAX; k++)
                test[i][j][k] = 1.0f;


    // column major order - SLOW
    for (int k = 0; k < MAX; k++)
        for (int j = 0; j < MAX; j++)
            for (int i = 0; i < MAX; i++)
                test[i][j][k] = 1.0f;
}

// Copy s2 to s1 using the array notation.
void CopyWithArrayNotation(char *s1, const char *s2)
{
    for (int i = 0; (s1[i] = s2[i]) != '\0'; i++)
        ;
}

// Copy s2 to s1 using the pointer notation.
void CopyWithPointerNotation(char *s1, const char *s2)
{
    for (; (*s1 = *s2) != '\0'; s1++, s2++)
        ;
}

void ArrayNotations()
{
    // Copy a string using the array notation and the pointer notation.
    char dest[20];
    char src1[] = "Array notation";
    char src2[] = "Pointer notation";

    // Copy src1 --> dest.
    CopyWithArrayNotation(dest, src1);
    cout << "dest = " << dest << endl;

    // Copy src2 --> dest.
    CopyWithPointerNotation(dest, src2);
    cout << "dest = " << dest << endl;

    // Print a string using the array notation and the pointer notation.
    for (int i = 0; src1[i] != 0; i++) // array notation
        cout << src1[i];
    cout << endl;

    for (char* p = src2; *p != 0; p++) // pointer notation
        cout << *p;
    cout << endl;
}
