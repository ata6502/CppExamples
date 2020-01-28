#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;

/*
    There are two ways to write an overloaded operator: 
    - As a member function.
    - As a free function. A free function may be a friend of a class.
    
    When you write a class you should always try to overload operators as member functions.
*/
namespace OperatorOverloadingExamples
{
    class Book
    {
    public:
        Book(std::string title, std::string author, int price)
            : m_title(title), m_author(author), m_price(price) { }

        std::string GetTitle() const { return m_title; }
        int GetPrice() const { return m_price; }

        // A member operator compares this book's price to another book's price.
        bool operator<(const Book& book) const
        {
            return m_price < book.m_price;
        }

        // A member operator compares this book's price to an integer.
        bool operator<(int price) const
        {
            return m_price < price;
        }

        // A friend function compares an integer to the price of a book.
        // Effectively, this function extends the int type to allow for comparison to a book.
        // It could be a free function rather than a friend if we exposed the books's price as 
        // a public accessor.
        // Note that this is not a declaration of the function. The following line
        // specifies that the function is able to access Book's private members.
        friend bool operator<(int price, const Book& book);

    private:
        std::string m_title;
        std::string m_author;
        int m_price;
    };

    // The declaration and the implementation of the friend function.
    bool operator<(int price, const Book& book)
    {
        return price < book.m_price;
    }

    void BookTest()
    {
        Book b1 = Book("AAA", "Author1", 100);
        Book b2 = Book("BBB", "Author2", 80);

        // Book::operator<(Book&)
        if (b1 < b2)
            cout << b1.GetTitle() << " is cheaper than " << b2.GetTitle() << ", ";
        else
            cout << b1.GetTitle() << " is more expensive than " << b2.GetTitle() << ", ";

        // Book::operator<(int)
        if (b2 < 90)
            cout << b2.GetTitle() << " costs less than $90" << ", ";
        else
            cout << b2.GetTitle() << " costs more than $90" << ", ";

        // friend operator<(int, Book&)
        if (200 < b1)
            cout << b1.GetTitle() << " costs more than $200" << ", ";
        else
            cout << b1.GetTitle() << " costs less than $200" << ", ";

        // Output:
        // AAA is more expensive than BBB
        // BBB costs less than $90
        // AAA costs less than $200
    }

    struct Vector2D
    {
        float X, Y;

        // default vector (0,0)
        Vector2D(void) : X(0), Y(0) {}

        // param ctor 
        Vector2D(float x, float y) : X(x), Y(y) {}

        // copy ctor
        Vector2D(const Vector2D& v) : X(v.X), Y(v.Y) {}

        // destr    
        ~Vector2D(void) {}

        // adding two vectors
        Vector2D operator+(const Vector2D &v)
        {
            return Vector2D(X + v.X, Y + v.Y);
        }

        Vector2D& operator+=(const Vector2D &v)
        {
            X += v.X;
            Y += v.Y;

            return *this; // operation chaining using the 'this' pointer
        }

        // Multiplication of a vector by a scalar.
        // In order to facilitate commutativity, two implementations 
        // of the "Multiply by Scalar" operator are provided as 
        // friend functions. 
        friend Vector2D operator*(float f, Vector2D v);
        friend Vector2D operator*(Vector2D v, float f);
    };

    Vector2D operator*(float f, Vector2D p)
    {
        return Vector2D(f * (float)p.X, f * (float)p.Y);
    }

    Vector2D operator*(Vector2D p, float f)
    {
        return Vector2D(f * (float)p.X, f * (float)p.Y);
    }

    // Overload the << operator to output Vector2D.
    std::ostream& operator<<(std::ostream& os, const Vector2D& v)
    {
        os << "(" << v.X << ", " << v.Y << ")";
        return os;
    }

    void VectorTest()
    {
        Vector2D vec = Vector2D(1.f, 2.f);

        Vector2D v1 = 2.f * vec;
        Vector2D v2 = vec * 3.f;

        cout << "v1=" << v1 << " ";
        cout << "v2=" << v2 << " ";
        cout << "v1+v2=" << v1 + v2 << " "; // add two vectors

        Vector2D v3 = Vector2D(3.f, 4.f);
        v3 += v1; // operation chaining
        cout << "v3=" << v3 << " ";
    }

    void Test()
    {
        BookTest();
        VectorTest();
    }
}