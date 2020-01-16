#pragma once

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;

/*
    The rule of three. Always write the following three methods when you implement manual memory management:
    1. The **copy constructor** - used to initialize an object with a different object of the same type.
       It defines how an object is passed by value. Pass-by-value can be read as "call the copy constructor."
    2. The **copy assignment operator** - used to copy the value from one object to another of the same type.
    3. The **destructor**.

    With the move operation available, we have the rule of five now.

    How to distinguish between a copy constructor and a copy assignment:
    - If a new object is being defined, a constructor is called.
    - If no new object is being defined, it is an assignment (no constructor is involved).

    Friend functions are ordinary global functions but they have access to all members (including private and protected) of a class.
    The prototype of a friend function (or a whole definition) has to be included in the class definition.
    Friend functions are not members of the class.

    - Make use of accessors when they exist, even within the class.
    - A pointer to a derived class can be stored as a pointer to the base class instead (Liskov substitution rule).
      - Any base class function can be called through such a pointer.
      - When the function is virtual - the derived class implementation is called.
      - When the function is non-virtual - the base class implementation is called.
    - The same rules of polymorphism and inheritance apply to smart pointers.

    Slicing: If you copy objects, slicing can occur
    - Copy a derived object into a base object - extra memeber variables fall away
    - Can't copy a base object into a derived object
    - Same rules apply when passing a parameter to a function by value: a copy is made, slicing will happen
      - That't why it's important to pass parameters to a function using references or pointers to avoid slicing
*/

namespace ClassesExamples
{
    namespace PersonExamples
    {
        class Person
        {
        public:
            Person(const string& name) : m_name(name) {}
            Person() : Person(string()) {} // default ctor calling a named ctor
            // Person() = default; // create a default ctor
            Person(const Person&) = delete; // remove the default copy ctor i.e., make the class non-copyable
            Person& operator=(Person const&) = delete; // remove the assignment operator

            virtual ~Person() { } // declare your destr virtual if there is at least one virtual method in the class
            virtual string GetName() const { return m_name; }
        private:
            string m_name;
        };

        class Employee : public Person
        {
        public:
            Employee(const string& name) : Person(name) {}
            // 'override' is optional but it is a good practice to include it
            string GetName() const override { return Person::GetName() + "(derived)"; }
        };

        //
        // Test Person and Employee
        //
        void Test()
        {
            // shared_ptr and polymorphism
            std::shared_ptr<Person> a = std::make_shared<Person>("A");
            cout << a->GetName() << " "; // A 

            std::shared_ptr<Person> b = std::make_shared<Employee>("B");
            cout << b->GetName() << " "; // B(derived) 

            std::shared_ptr<Employee> c = std::make_shared<Employee>("C");
            cout << c->GetName() << " "; // C(derived)

            Person person("Per");
            Employee employee("Emp");

            // Get a Person reference from an Employee reference (downcast: get base class from derived).
            Person& pr = employee;

            // Get an Employee reference from a Person reference (upcast: derived class from base class).
            // It is valid because we know that pr came from Employee.
            Employee& er1 = static_cast<Employee&>(pr);
            cout << er1.GetName() << " "; // Emp(derived)

            // Better yet, you can use the dynamic_cast because static_cast does not check if pr
            // is really of Employee type or derived from Employee.
            // Note that you can use dynamic_cast only on a class with a virtual function.
            Employee& er2 = dynamic_cast<Employee&>(pr);
            cout << er2.GetName() << " "; // Emp(derived)

            // dynamic_cast throws an exception when reference casting is not valid.
            try
            {
                // We know this cast will fail because person is of type Person, not Employee&.
                Employee& x = dynamic_cast<Employee&>(person);
            }
            catch (const std::bad_cast&)
            {
                cout << "CastError ";
            }

            // dynamic_cast returns nullptr if pointer casting is not valid.
            Person* pp = &person;
            Employee* ep = dynamic_cast<Employee*>(pp); // ep is nullptr
            cout << (ep == nullptr ? "NULL" : "OK") << " ";
        }
    }


    namespace ClassConstants
    {
        class TestClass
        {
        public:
            // constants have to be declared as static 
            static const int a = 1; // usage TestClass::a

            // a static member
            static int b;
        };

        // Static members have to be initialized outside of the class definition.
        int TestClass::b = 2;
    }


    namespace ComplexExamples
    {
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

            // Re-allocate any resources needed. 
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

        void Test()
        {
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
        }
    }


    namespace ObjectLifecycle
    {
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

        void Test()
        {
            // The order of calls:
            // 1. Base ctor
            // 2. Derived ctor
            // 3. Derived destr
            // 4. Base destr
            Derived derived(8);
        }
    }


    namespace MutableMemberExamples
    {
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

        void Test()
        {
            cout.setf(std::ios_base::boolalpha);

            MutableMember obj;
            obj.ShowFormatted();
            obj.Format();
            obj.ShowFormatted();
        }
    }


    namespace SlicingProblem
    {
        class Base
        {
        public:
            Base(int a) : m_a(a) { }
            virtual int Get() const { return m_a; }
        private:
            int m_a;
        };

        class Derived : public Base
        {
        public:
            Derived(int a, int b) : Base(a), m_b(b) {  }
            int Get() const override { return m_b; }
        private:
            int m_b;
        };

        void Test()
        {
            Base x(1);
            //Derived y = x; // compile error: no suitable conversion from Base to Derived exists

            Derived d(11, 22);

            Base b1 = d; // copy m_a but not m_b because m_b does not exist in Base
            cout << b1.Get() << " "; // 11 - Slicing: q.Get calls the Base's version of Get

            // A solution to keep polymorphism: use pointers and references.
            Base* b2 = &d;
            cout << b2->Get() << " "; // 22

            // A nicer solution. References are polymorphic in the same way as pointers.
            Base& b3 = d;
            cout << b3.Get() << " "; // 11
        }
    }


    void Test()
    {
        PersonExamples::Test();
        ComplexExamples::Test();
        ObjectLifecycle::Test();
        MutableMemberExamples::Test();
        SlicingProblem::Test();
    }
}











