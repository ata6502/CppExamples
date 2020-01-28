#pragma once

#include <iostream>
#include <memory> // std::swap
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

/*
    Vector performs well because it implements move semantics i.e., it moves its elements rather then copying them.
    String performs well because it implements move semantics when concatenating strings.
    If an object is moveable, it will be moved if there is an appropriate move sematics defined.

    Compiler generates a default move ctor for you if you have moveable contents.

*/

namespace MoveSemanticsExamples
{
    int get() { return 8; }
    class Book { };

    // An example of an r-value:
    // in x = a + b the expression a + b is an rvalue because once we have the value, the expression goes away.
    void RValue()
    {
        // get() is an rvalue
        // x is an rvalue reference
        int&& x = get();
        cout << x << " ";

        Book books[10];

        // Problem: An instance of Book is created and then another instance 
        // is created when copied to books[7].
        books[7] = Book();

        // Solution: Use an array of pointers to avoid the unnecessary copy.
        Book* pbooks[10];
        pbooks[7] = new Book();
        // ...
        delete pbooks[7];

        // But: We are not able to create an array of references.
        // Book& rbooks[10]; // does not compile

        // Better solution: Use move semantics to avoid double copy.
        // std::move accepts a regular reference and casts it to an rvalue reference. 
        books[7] = std::move(Book()); // reallocate the address of a Book instance to books[7]

        // The argument of std::move is an rvalue.
        int q = std::move(get());
        cout << q << " ";
    }

    void Swapping()
    {
        // Swapping using references.
        auto swap = [](int& x, int& y)
        {
            // Problem: We use tmp as a temporary storage which we delete immediately
            // after copying. We don't want to copy x to tmp, we want to move 
            // the memory of x to tmp. The same applies to the statement y = tmp.
            // We don't want to perform a copy, we want to move memory.
            int tmp{ x };
            x = y;
            y = tmp;
        };

        int x = 2, y = 5;
        swap(x, y);

        // Solution: Eliminate the extra allocations by swapping using move sematics.
        auto betterSwap = [](int& x, int& y)
        {
            // The argument of std::move is an rvalue.
            int tmp{ std::move(x) };
            x = std::move(y);
            y = std::move(tmp);
        };

        betterSwap(x, y);

        // There is a built-in swap function in std.
        // std::swap uses move sematics to eliminate the extra allocations.
        std::swap(x, y);
    }

    void Test()
    {
        RValue();
        Swapping();
    }
}

