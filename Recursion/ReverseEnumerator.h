#pragma once

#include <iostream>

using std::cout;
using std::endl;

void print(int a[], int index, int arraySize)
{
    if (index < arraySize)
    {
        cout << a[index] << " ";
        print(a, index + 1, arraySize);
    }
    else
    {
        return;
    }
}

void reverse(int a[], int index, int firstIndex)
{
    if (index >= firstIndex)
    {
        cout << a[index] << " ";
        reverse(a, index - 1, firstIndex);
    }
    else
    {
        return;
    }
}

// ReverseEnumerator prints an array of integers in the stored order and in the reverse order.
void ReverseEnumerator()
{
    cout << "*** Reverse Enumerator ***" << endl;

    int a[] = { 0,1,2,3,4 };
    const int arraySize = sizeof(a) / sizeof(int);

    print(a, 0, arraySize); // accepts first index and the array size
    cout << endl;

    reverse(a, arraySize-1, 0); // accepts last index and first index
    cout << endl;

    cout << endl;
}
