#pragma once

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;

/*
    unique_ptr
    - non-copyable
    - you can use std::move to move values in and out of unique_ptr
    - works well in containers
    - less overhead than shared_ptr
    - if an object is in a unique_ptr, give access to it through a raw pointer (the get method)
      - you DO NOT control the object's lifetime through the raw pointer
      - test unique_ptr before calling get
    - use reset() to re-initialize the unique_ptr with a new value: uptr.reset(new MyClass()); 
      - the new object is created first and then the old object is cleaned up 
      - this saves you from self-assigment as well as from the case if the ctor throws an exception (the old object is still valid)
      - if you want to remove the old object first, just call reset with no parameters; this sets nullptr and clears up the object the pointer was pointing to

    shared_ptr
    - reference counted
    - non-intrusive
    - works well in containers
    - make_shared improves performance
    - use reset() to decrement the counter of a shared pointer and possibly delete it
    - you don't need the copy ctor and assignment operator to copy/assign the object that holds a shared_ptr
    - if an object is in a shared_ptr, give access to it through a weak_ptr

    weak_ptr
    - originates from a shared_ptr to give access to the pointed object

    When you need a pointer:
    1. To represent UML composition (has-a) as a class's member variable. Lifetime of the variable is tied to the class.
      - Make the variable a solid member of your class.
      - When the containing object is copied, solid members are copied too.
      - When the containing object is destroyed, all solid objects are also destroyed including all collections and their elements.
      - Use a unique_ptr when the member variable is optional or really large.
        - In such case, you need to write a copy ctor and assignment operator for your class. Otherwise, you class will be non-copyable.

    2. To access something, e.g., a pointer to the owner or a list of resources that outlive your object. Note that in this case you don't 
       have control over the lifetime of the objects referenced by the pointers. 
       - if an object is in a unique_ptr, give access to it through a raw pointer
       - if an object is in a shared_ptr, give access to it through a weak_ptr
       - if an object is solid, give access to it through a raw pointer using the & operator or 'this'

       You do not have to use smart pointers for everything. When you use a pointer to just observe, use can use a raw pointer.

    3. To allow shared access to an object on the free store. The object does not have a single owner.
       - Lifetime can be complicated to manage.

    Smart pointers have operator overloads to bool. You still can write if (p) { ... }
*/
namespace SmartPointersExamples
{
    //
    // unique_ptr
    //
    class Book 
    { 
    public:
        Book(const string& title) : m_title(title) 
        { 
            cout << "Create:" << m_title << " ";
        }
        ~Book()
        {
            cout << "Destroy:" << m_title << " ";
        }
        string GetTitle() const { return m_title; }
    private:
        string m_title;
    };

    std::unique_ptr<Book> CreateBook1(const string& title)
    {
        return std::unique_ptr<Book>(new Book(title));
    }

    std::unique_ptr<Book> CreateBook2(const string& title)
    {
        auto* pb = new Book(title);
        // ... manipulate the Book object
        return std::unique_ptr<Book>(pb); // wrap a raw pointer around a unique_ptr
    }

    std::unique_ptr<Book> CreateBook3(const string& title)
    {
        return std::make_unique<Book>(title); // use the utility function make_unique
    }

    // just a helper
    class Address
    {
    public:
        Address(const string& city) : m_city(city) { cout << "aCtor "; }
        ~Address() { cout << "aDestr "; }
        string ToString()
        {
            return m_city;
        }
    private:
        string m_city;
    };


    //
    // unique_ptr
    //
    // A class with a unique_ptr field as a member variable. Because it is a pointer
    // it means the variable is optional.
    class Customer
    {
    public:
        Customer(const string& name)
            : m_name(name)
        { }

        // TODO: a shitty pattern; the user is required to call SetAddress before calling GetCity
        void SetAddress(const string& city)
        {
            m_pAddress.reset(new Address(city));
        }

        string GetCity() const
        {
            return m_pAddress->ToString();
        }

        string ToString() 
        { 
            return m_name + "-" + m_pAddress->ToString(); 
        }

        // If we want to copy the Customer.

        // copy ctor
        Customer(const Customer& c)
            : m_name(c.m_name)
        {
            // Create a new address and put it to the unique_ptr.
            m_pAddress.reset(new Address(c.GetCity()));
        }

        // assignment operator 
        Customer& operator=(const Customer& c)
        {
            m_name = c.m_name;

            // Create a new address and put it to the unique_ptr.
            // You don't need to worry about the self-assignment.
            // unique_ptr takes care about it for you.
            m_pAddress.reset(new Address(c.GetCity()));

            return *this;
        }

    private:
        string m_name;

        std::unique_ptr<Address> m_pAddress;

        // If we want to make the Customer non-copyable.
        // Customer(const Customer&); // private copy ctor
        // Customer& operator=(const Customer&); // private assignment operator
    };


    //
    // shared_ptr
    //
    class Person
    {
    public:
        Person(const string& city)
        {
            m_pAddress = std::make_shared<Address>(city);
            cout << "CreatePerson ";
        }
        ~Person()
        {
            cout << "DestroyPerson ";
        }

        std::shared_ptr<Address> GetAddress() const 
        {
            return m_pAddress;
        }
    private:
        std::shared_ptr<Address> m_pAddress;
    };

    void Test()
    {
        //
        // unique_ptr
        //

        // unique_ptr is useful for returning a heap-allocated variable
        // from a function.
        {
            auto b1 = CreateBook1("AAA");
        }

        // The unique_ptr object cannot be shared (copied).
        // Also, if you have a class containing a unique_ptr you will not be able to copy it either.
        //auto bb(b1); // does not compile; the copy ctor and the copy assignment ares declared as 'delete'
        //auto bb = b1;

        {
            Customer c1("Cus");
            c1.SetAddress("Adr");
            cout << c1.ToString() << " ";

            // We need a copy ctor and a copy assignment operator to make it work.
            Customer c2 = c1; // copy ctor
            c1 = c2; // assignment operator
        }

        //
        // shared_ptr
        //
        // The person's address does not get destroyed together with the person because it is 
        // a shared_ptr
        std::shared_ptr<Address> pAddress;

        {
            Person person("BBB");
            pAddress = person.GetAddress(); // here, the shared_ptr's reference counter is increased 
                                           // which prevents the address from being destroyed when 
                                           // the person goes out of scope

            Person p2 = person; // no copy ctor called on the Address member because it is shared between person and p2 !!! (performance improvement)
            person = p2; // no assigment operator called on the Address
        }

        pAddress->ToString();

        //
        // nullptr - type safety
        //
        // You can write if(pi) and if(!pi) also with smart pointers. 
        int i = 2;
        int* pi = nullptr;
        if (!pi) // conversion to bool
            pi = &i;
        if (pi) // conversion to bool
        {

        }
    }
}