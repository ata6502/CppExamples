#pragma once

#include <iostream>

using std::cout;
using std::endl;

/*
    The rule of three. Always write these three methods when you have manual memory management:
    1. The **copy constructor** is used to initialize an object with a different object of the same type.
       It defines how an object is passed by value. Pass-by-value can be read as "call the copy constructor."
    2. The **copy assignment operator** is used to copy the value from one object to another of the same type.
    3. The **destructor**.

    How to distinguish between a copy constructor and a copy assignment:
    - If a new object is being defined, a constructor is called.
    - If no new object is being defined, it is an assignment (no constructor is involved).

    Friend functions are ordinary global functions but they have access to all members (including private and protected) of a class.
    The prototype of a friend function (or a whole definition) has to be included in the class definition.
    Friend functions are not members of the class.

    Good practices:
    - Make use of accessors when they exist, even within the class.
*/

class Complex
{
public:
    // ctors
    Complex();
    Complex(double r, double i);

    // copy ctor
    Complex(const Complex& z);

    // copy assignment operator
    Complex& operator=(const Complex& z);

    // accessors
    double Re() const { return re; }
    double Im() const { return im; }
    void Set(double r, double i) { re = r; im = i; }

    // a friend function; the access attributes (private, public, protected) do not apply to friend functions
    friend void Display(const Complex z);

private:
    double re, im;
};

// default ctor
Complex::Complex() :
    re(0.0), im(0.0)
{ }

// ctor with parameters
Complex::Complex(double r, double i) :
    re(r), im(i)
{ }

// copy ctor
// - we have access to the private data members re and im
// - copy all members in a copy ctor
Complex::Complex(const Complex& z) :
    re(z.re), im(z.im)
{
    cout << "CopyCtor ";

    // Allocate any resources needed.
    // pResource(new Resource());
}

// copy assignment operator
// - no new object is defined and no ctor involved
// - assignment operator should deallocate any memory allocated by the default ctor and allocate new memory
Complex& Complex::operator=(const Complex& z)
{
    cout << "CopyAssignmentOperator ";

    // A resource already exists. Re-allocate any resources needed. 
    // delete pResource;
    // pResource = new Resource();

    // protect against self-assignment
    if (this != &z) // is it self-assignment?
    {
        re = z.re;
        im = z.im;
    }

    // 'this' - A pointer to an object for which operator= was invoked. 'this' is of type Complex*
    //          It is not possible to take the address of 'this'.
    // '*this' - Refers to an object for which operator= was invoked i.e. *this is the object.

    return *this;
}

// Friend function definition.
void Display(const Complex z)
{
    cout << "z=(" << z.re << ", " << z.im << ") ";
}



class Base
{
public:
    Base(int a) { cout << "BaseCtor "; }
    ~Base() { cout << "BaseDestr "; }
};

class Derived : public Base
{
public:
    Derived(int a) : Base(a) { cout << "DerivedCtor "; }
    ~Derived() { cout << "DerivedDestr "; }
};



class MutableMember
{
private:
    // The isFormatted member can be modified even by 
    // const members because it is marked as mutable.
    mutable bool isFormatted;

public:
    MutableMember();
    void ShowFormatted();

    // The Format method demonstrates the use of the 'mutable' storage specifier.
    // The const function Format is able to modify isFormatted because isFormatted
    // is marked as mutable.
    void Format() const;
};

MutableMember::MutableMember() : 
    isFormatted(false)
{ }

void MutableMember::ShowFormatted()
{
    cout << "IsFormatted=" << isFormatted << " ";
}

// The Format method demonstrates the use of a mutable member. 
// To implement logical constness use the mutable storage specifier rather 
// than the const_cast operator.
void MutableMember::Format() const
{
    // Use the mutable storage specifier when declaring isFormatted.
    // If isFormatted was not marked as mutable the code would not compile.
    if (!isFormatted)
    {
        isFormatted = true;

        // do some fancy formatting
        // ...
    }
}



void Classes()
{
    //
    // TestComplex
    //
    // Note: We are not using a custom output operator << because it would require an additional
    // call to the copy ctor. This would make the calls unclear.

    Complex z; // invoke the default ctor
    cout << "z=(" << z.Re() << ", " << z.Im() << ") ";

    Complex z1(1.1, 2.3); // invoke the param ctor
    cout << "z1=(" << z1.Re() << ", " << z1.Im() << ") ";

    Complex z2(z1); // invoke the copy ctor
    cout << "z2=(" << z2.Re() << ", " << z2.Im() << ") ";

    z2.Set(8.0, 4.2);
    z1 = z2; // invoke copy assignment operator
    cout << "z1=(" << z1.Re() << ", " << z1.Im() << ") ";

    Complex z3 = z1; // invoke copy constructor
    cout << "z3=(" << z3.Re() << ", " << z3.Im() << ") ";

    // Create an array of objects. The default ctor is called six times.
    Complex numArray[3];

    // Create a vector of objects. The default ctor is called six times.
    std::vector<Complex> numVector = std::vector<Complex>(3);

    cout << "Friend: ";
    Display(z);


    //
    // TestCtorDestrOrder
    //
    // The order of calls:
    // 1. Base ctor
    // 2. Derived ctor
    // 3. Derived destr
    // 4. Base destr
    {
        Derived derived(8);
    }

    //
    // TestMutableMember
    //
    cout.setf(std::ios_base::boolalpha);

    MutableMember obj;
    obj.ShowFormatted();
    obj.Format();
    obj.ShowFormatted();
}












