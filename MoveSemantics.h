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
    - Pass by value: if a temp is passed to a function, it can be moved, not copied.
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
        // rvalue is something that goes away:
        // in x = a + b the expression a+b is an rvalue because at the moment we have
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
            // We use tmp as a temporary storage which we delete immediately
            // after copying. We don't want to copy x to tmp, we want to move 
            // the memory of x to tmp. We don't care what happens to x after 
            // the move because x is overridden in the next statement x = y.
            // The same applies to the next statement y = tmp: we don't want 
            // to perform a copy, we want to move memory.
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
        // default constructor
        Resource() : m_name{ "" }
        {
            cout << "dc,";
        }

        // explicit named (aka ordering) constructor
        Resource(string name) : m_name{ name }
        { 
            cout << "nc" << m_name << ","; 
        }

        // copy constructor
        Resource(Resource const & other) : m_name{ other.m_name } 
        { 
            cout << "cc" << m_name << ","; 
        }

        // move constructor
        // - accepts Resource rvalue reference
        // - does not have 'const' specified in its parameter because we want to modify the original
        // - after executing this ctor, other.m_name is an empty string
        Resource(Resource&& other) 
            : m_name(std::move(other.m_name)) 
        {
            cout << "mc" << m_name << ","; 
        }

        ~Resource()
        {
            cout << "d" << m_name << ",";
        }

        // copy assignment operator
        Resource& operator=(const Resource& other)
        {
            cout << "co" << m_name << ",";
            m_name = other.m_name; // no need to care about self-assignment because we just copy the name
            return *this;
        }

        // move assignment operator
        Resource& operator=(Resource&& other)
        {
            // Check for self-assignment.
            if (this != &other)
            {
                cout << "mo" << other.m_name << ",";
                m_name = std::move(other.m_name);
                other.m_name.clear(); // clear the old value; not required but just to be on the safe side
            }
            return *this;
        }

        void swap(Resource& other)
        {
            cout << "sw" << m_name << other.m_name << ",";
            std::swap(m_name, other.m_name);
        }

    private:
        string m_name;
    };

    // Allows the standard algorithms to find the Resource's swap function.
    void swap(Resource& left, Resource& right)
    {
        left.swap(right);
    }

    // Illustrates how user-defined types behave with vector and list.
    void MovementWithContainers()
    {
        {
            auto c = list<Resource>{};
            c.emplace_back();       // default ctor
            c.clear();              // destr
            cout << " ";
        }

        {
            auto c = list<Resource>{};
            c.emplace_back("A");    // named ctor
            c.clear();              // destr
            cout << " ";
        }

        {
            // push_back allocates some storage for the Resource inside the container. 
            // The state of the Resource is then moved from the first rvalue to the Resource 
            // within the container. The first Resource whose state was moved away still exists 
            // and is quickly destroyed. 

            // push_back doesn't depend on move semantics. If the type being contained doesn't 
            // have a move constructor it will attempt to copy the object.

            // If the Resource class did not define a move ctor:

            // push_back would use the copy ctor and create a new object copying or moving the value of its arguments.
            // c.push_back(Resource{ "B" }); // ncB (named ctor), ccB (copy ctor), dB (destr)

            // emplace_back would avoid the temporary object and construct the element in place.
            // The argument is forwarded to the Resource's named ctor inside the container.
            // c.emplace_back("B"); // ncB (named ctor)

            auto c = list<Resource>{};
            c.emplace_back("B"); // named ctor, move ctor, destr of the empty temporary that has been moved
            c.clear();              // destr of B
            cout << " ";
        }

        {
            auto c = list<Resource>{};
            c.emplace_back("A");    // ncA
            c.emplace_back("B");    // ncB
            c.emplace_back("C");    // ncC
            c.emplace_back("D");    // ncD
            c.emplace_back("E");    // ncE
            cout << " ";

            // Use the list's reverse method.
            c.reverse();            // the list container knows how to reverse the order of its elements without having to move, copy, or swap them
        } // dE,dD,dC,dB,dA
        cout << " ";

        // ??? Why the copy ctor is preferred rather than the copy ctor?

        // When copy ctor is defined on Resource:
        {
            auto c = vector<Resource>{};
            c.emplace_back("A");    // ncA
            c.emplace_back("B");    // ncB,ccA,dA
            c.emplace_back("C");    // ncC,ccA,ccB,dA,dB
            c.emplace_back("D");    // ncD,ccA,ccB,ccC,dA,dB,dC
            c.emplace_back("E");    // ncE,ccA,ccB,ccC,ccD,dA,dB,dC,dD
            cout << " ";

            // Use the standard reverse algorithm.
            std::reverse(std::begin(c), std::end(c)); // swAE,swBD   
            
            // If swap was not defined: mcA,moE,moA,d,mcB,moD,moB,d
            // the reverse algorithm would have to use the generic swap algorithm. For every swap it needs to create a temporary.
        } // dA,dB,dC,dD,dE
        cout << " ";

        // When copy ctor is not defined on Resource:
        {
            auto c = vector<Resource>{};
            c.emplace_back("A");    // ncA
            c.emplace_back("B");    // ncB,mcA,d
            c.emplace_back("C");    // ncC,mcA,mcB,d,d
            c.emplace_back("D");    // ncD,mcA,mcB,mcC,d,d,d
            c.emplace_back("E");    // ncE,mcA,mcB,mcC,mcD,d,d,d,d
            cout << " ";

            std::reverse(std::begin(c), std::end(c)); // swAE,swBD

        } // dA,dB,dC,dD,dE
        cout << " ";
    }

    void Test()
    {
        RValue();
        Swapping();
        MovementWithContainers();
    }
}