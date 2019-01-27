#pragma once

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;

namespace SmartPointersExamples
{
    //
    // Book demonstrates unique_ptr
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


    //
    // Person and Address demonstrates shared_ptr
    //
    class Address 
    { 
    public:
        Address(const string& city) : m_city(city) { }
        void ToString()
        {
            cout << m_city << " ";
        }
    private:
        string m_city;
    };

    class Person
    {
    public:
        Person(const string& city)
        {
            m_address = std::make_shared<Address>(city);
            cout << "CreatePerson ";
        }
        ~Person()
        {
            cout << "DestroyPerson ";
        }

        std::shared_ptr<Address> GetAddress() const 
        {
            return m_address;
        }
    private:
        std::shared_ptr<Address> m_address;
    };

    void SmartPointers()
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


        //
        // shared_ptr
        //
        // The person's address does not get destroyed together with the person because it is 
        // a shared_ptr
        std::shared_ptr<Address> address;
        {
            Person person("BBB");
            address = person.GetAddress(); // here, the shared_ptr's reference counter is increased 
                                           // which prevents the address from being destroyed when 
                                           // the person goes out of scope
        }
        address->ToString();
    }
}