#pragma once

#include <iostream>
#include <memory> // std::swap

using std::cout;
using std::endl;

namespace MoveSemanticsExamples
{
    class Book { };

    int get()
    {
        return 83;
    }

    void RValue()
    {
        // get() is an rvalue
        // x is an rvalue reference
        int&& x = get();
        cout << x << " ";

        Book books[10];

        // PRB: An instance of Book is created and then another instance 
        // is created when copied to books[7].
        books[7] = Book();

        // A solution is to keep pointers to avoid
        // the unnecessary copy.
        Book* pbooks[10];
        pbooks[7] = new Book();
        // ...
        delete pbooks[7];

        // We are not able to create an array of references.
        // Book& rbooks[10]; // does not compile

        // The better solution is to use move semantics to avoid double copy.
        // This reallocates the address of the Book instance to books[7]
        books[7] = std::move(Book());

        // The argument of std::move is an rvalue.
        int q = std::move(get());
    }

    void Swapping()
    {
        // Swapping using references.
        auto swap = [](int& x, int& y)
        {
            // PRB: We copy x to tmp and then y to x and then tmp to y.
            // There are too many copy operations. Also, we duplicate 
            // the amount of memory we need.
            // We don't want to copy x to tmp, we want to move the memory
            // of x to tmp. We don't care what happens to x after the move
            // because x is overridden in the next statement x = y.
            // The same applies to next statements: we don't want to perform
            // a copy, we want to move memory.
            int tmp{ x };
            x = y;
            y = tmp;
        };

        int x = 2, y = 5;
        swap(x, y);

        // Swapping using move sematics.
        // We eliminate the extra allocations.
        auto betterSwap = [](int& x, int& y)
        {
            // The argument of std::move is an rvalue.
            int tmp{ std::move(x) };
            x = std::move(y);
            y = std::move(tmp);
        };

        betterSwap(x, y);

        // Swapping using std::swap
        // std::swap uses move sematics to eliminate the extra allocations.
        std::swap(x, y);
    }

    void MoveSemantics()
    {
        RValue();
        Swapping();
    }
}