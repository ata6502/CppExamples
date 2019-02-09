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
    Move semantics applies to objects that are handles i.e., objects that have a reference 
    to data stored somewhere else, for example on the free store. Copying the referenced
    data to another object takes time. If you don't need the reference any more, you can 
    just move the pointer to another object.

    Avoid unnecassary copying by defining a move ctor and a move assignment operator in your class.

    You can write a variaty of functions that take rvalue reference:
    - Pass by value: is a temp is passed to a function, it can be moved, not copied.
    - Return by value: a local variable is about to go out of scope - a great candidate for moving.
    - Moving a unique_ptr into and out of a collection.
    Vector performs well because it implements move semantics i.e., it moves its elements rather then copying them.
    String performs well because it implements move semantics when concatenating strings.
    If an object is moveable, it will be moved if there is an appropriate move sematics defined.
    Standard library containers (including strings) use move semantics.

    Compiler generates a default move ctor for you if you have moveable contents.

    std::move takes a regular reference and casts it to an rvalue reference. 
*/
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
        // rvalue is something that goes away; it's something you can "steal" from
        // In x = a + b the expression a+b is an rvalue because at the moment we have
        // the value, the expression goes away.
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

    class Resource
    {
    public:
        // ctor
        Resource(string name) : m_name(name) { cout << "c" << m_name << ","; }

        // copy ctor
        Resource(const Resource& r) : m_name(r.m_name) { cout << "cc" << m_name << ","; }

        // assignment operator
        Resource& operator=(const Resource& r)
        {
            cout << "co" << m_name << ",";
            // We don't need to care about self-assignment because we just copy the name.
            m_name = r.GetName();
            return *this;
        }

        // move ctor; accepts Resource rvalue reference
        // IMPORTANT: move ctor (unlike copy ctor) does not have 'const' specified in its parameter.
        // The reason is that when we copy we leave the original untouched but when we move, we want
        // to modify the original.
        // After executing this ctor, the other r won't have m_name anymore.
        Resource(Resource&& r) : m_name(std::move(r.m_name)) { cout << "mc" << m_name << ","; }

        // move assignment operator; accepts Resource rvalue reference
        Resource& operator=(Resource&& r)
        {
            // Check if we don't do the self-assignment. We need to chek it because std::move 
            // moves the m_name from r to here.
            if (this != &r)
            {
                cout << "mo" << m_name << ",";
                m_name = std::move(r.m_name);
                r.m_name.clear(); // clear out the old value; just to be on the safe side
            }
            return *this;
        }
        string GetName() const { return m_name; }
    private:
        string m_name;
    };

    void MoveCtor()
    {
        vector<Resource> v;

        Resource r("A");            // ctor
        v.push_back(r);             // copy ctor; r is not moveable because it has its own independent life outside of the vector

        // Resource("B") is a temp - the rvalue
        v.push_back(Resource("B")); // ctor
        
        // Increase the size of the vector and move all elements:
        // move B
        // ??? copy A - why not move ???
        // It looks like the Resource once inserted to the vector is not moveable, why ???

        std::for_each(begin(v), end(v),
            [](Resource r) { } // copy ctor is used here because we don't want to get rid of the original object
        );

        cout << " ";
    }

    void Test()
    {
        RValue();
        Swapping();
        MoveCtor();
    }
}