#pragma once

#include <iostream>
#include <string>
#include <memory> // unique_ptr, shared_ptr, weak_ptr

using std::cout;
using std::endl;
using std::string;

/*
    unique_ptr
    - exclusively owns an object to which it points (provides exclusive ownership semantics)
    - non-copyable (does not provide a copy ctor and a copy assignment operator)
    - can be moved (provides move ctor and move assignment)
      - you can use std::move to move an object in and out of unique_ptr to transfer ownership of the object
      - you can make the transfer of ownership in and out of a function explicit
    - works well in containers
    - provides an explicit conversion to bool to determine whether it holds a non-null pointer
    - has less overhead than shared_ptr
    - use the make_unique function template to create and allocate objects to be owned by unique_ptr
    - you can give access to an object pointed by a unique_ptr through a raw pointer (the get method)
      - DO NOT control the object's lifetime through the raw pointer
      - test unique_ptr before calling get
    - use reset() to re-initialize the unique_ptr with a new value: ptr.reset(new MyClass()); 
      - the new object is created first and then the old object is cleaned up 
      - if you want to remove the old object first, call reset with no parameters

    shared_ptr
    - shares the ownership of an object to which it points (implements shared ownership semantics)
    - provides non-invasive reference counting i.e., it wraps an object with a reference count
    - can be copied (provides a copy constructor and copy assignment)
    - can be moved (provides a move constructor and move assignment)
    - works well in containers
    - holds two pointers: one to the object being managed and another one to a control block
      the control block is a data structure that holds:
      - a strong ref count (strong use_count)
      - a weak ref count (weak use_count)
      - an optional deleter
    - use the make_shared function template to create shared_ptr
    - use reset() to decrement the counter of a shared pointer and possibly delete it
    - you can give access to an object pointed by a shared_ptr through a weak_ptr
    
    weak_ptr
    - originates from a shared_ptr and gives access to the pointed object
    - solves the problem of circular references in data structures and object graphs
    - use it when you need to refer to an object managed by shared_ptr without taking a strong reference
    - shared_ptr along with weak_ptr provide a lightweight form of garbage collection
*/
namespace SmartPointersExamples
{
    //
    // unique_ptr
    //
    namespace UniquePtrExamples
    {
        class Book
        {
        public:
            Book(const string& title) : m_title(title)
            {
                cout << m_title << " ";
            }
            ~Book()
            {
                cout << "~" << m_title << " ";
            }
            void SetTitle(const string& title) { m_title = title; }
        private:
            string m_title;
        };

        void ConstructUniquePtr()
        {
            // Create an empty unique_ptr that can hold a Book pointer.
            auto b1 = std::unique_ptr<Book>();                // value: empty
            auto b2 = std::unique_ptr<Book>{};                // value: empty
            auto b3 = std::unique_ptr<Book>{ nullptr };       // value: empty

            // Create a unique_ptr and initialize it with a pointer to a newly allocated Book object.
            auto b4 = std::unique_ptr<Book>(new Book("A"));   // value: unique_ptr {m_title={"A"}}
            auto b5 = std::unique_ptr<Book>(new Book{ "B" }); // value: unique_ptr {m_title={"B"}}

            // Wrap a unique_ptr around a raw pointer.
            auto* pb = new Book("C");
            auto b6 = std::unique_ptr<Book>(pb);              // value: unique_ptr {m_title={"C"}}

            // Create a unique_ptr using the utility function make_unique.
            auto b = std::make_unique<Book>("D");             // value: unique_ptr {m_title={"D"}}

            // You are not able to copy an object that contains a unique_ptr
            // auto cb = b; // compiler error (C2280) - the copy ctor and the copy assignment are declared as 'delete'
            // auto cb(b);  // compiler error (C2280) - the same as above
        } // destr: ~D ~C ~B ~A

        void TransferObjectOwnership()
        {
            auto b1 = std::make_unique<Book>("E");

            // unique_ptr provides an explicit conversion to Boolean.
            if (b1) cout << "b1 "; // book1 owns a Book object

            // Use move semantics to transfer the object ownership from 
            // the unique_ptr on the right to the unique_ptr on the left.
            auto b2 = std::move(b1);

            if (b1) cout << "b1 "; // book1 does not own the Book object anymore
            if (b2) cout << "b2 "; // book2 owns the Book object
        } // Book destr is called only once

        // Use a unique_ptr to return a heap-allocated variable from a function
        // i.e., transfer the ownership of an object from a function.
        std::unique_ptr<Book> GetBook(const string& title)
        {
            // Return a pointer to a Book object.
            return std::make_unique<Book>(title);
        }

        // Transfer the ownership of an object to a function. UpdateBook accepts 
        // a unique_ptr by value. Move the object into the UpdateBook function using std::move.
        std::unique_ptr<Book> UpdateBook(std::unique_ptr<Book> book)
        {
            book->SetTitle("X");
            return book;
        }

        void TransferOwnership()
        {
            // Transfer the ownership of an object from the GetBook function.
            auto q = GetBook("Q");

            // Move the object in and out of the function.
            q = UpdateBook(std::move(q));
        }

        // The BookWithPointer class contains a unique_ptr member variable. 
        // Because it is a pointer, the variable may be optional i.e. it 
        // may have the nullptr value.
        // We make the BookWithPointer copyable by defining a copy ctor
        // and a copy assignment operator.
        class Author { };
        class BookWithPointer
        {
        public:
            BookWithPointer(const string& title) : m_title(title) { }
            ~BookWithPointer() { }

            // Copy implementation (if needed).
            BookWithPointer(const BookWithPointer& b)
                : m_title(b.m_title)
            {
                // Create a new Author and put it to the unique_ptr.
                m_author.reset(new Author());
            }

            // assignment operator 
            BookWithPointer& operator=(const BookWithPointer& b)
            {
                m_title = b.m_title;

                // Create a new Author and put it to the unique_ptr.
                // unique_ptr takes care about self-assignment.
                m_author.reset(new Author());

                return *this;
            }

        private:
            string m_title;
            std::unique_ptr<Author> m_author;
        };

        void CopyObjectContainingUniquePtr()
        {
            BookWithPointer p("P");
            BookWithPointer cp = p; // copy ctor
            p = cp; // copy assignment operator
        }

        void UniquePtrMethods()
        {
            auto b = std::make_unique<Book>("F");

            // Create an independent copy. Modifying the copy doesn't affect 
            // the object owned by the smart pointer and vice versa.
            Book copy = *b;

            // Get a reference to the object owned by unique_ptr.
            Book& ref = *b;

            // Get the pointer itself using the get method.
            Book* ptr = b.get();

            // Get the pointer and also release the ownership of it.
            Book* ptr2 = b.release(); // b is empty

            // Delete the owned object. 
            b.reset(); // at this point the unique_ptr no longer points to anything

            // Assume ownership of a raw pointer.
            b.reset(ptr); // now the unique_ptr owns the original Book object

        } // Book destr called twice: ~F ~F

        void Test()
        {
            ConstructUniquePtr();
            TransferObjectOwnership();
            TransferOwnership();
            CopyObjectContainingUniquePtr();
            UniquePtrMethods();
        }
    }

    void assert(bool condition)
    {
        if (!condition)
            cout << "ERROR ";
    }

    //
    // shared_ptr
    //
    namespace SharedPtrExamples
    {
        class Book { };

        // a library with one book
        class Library
        {
        public:
            Library()
            {
                m_book = std::make_shared<Book>();
                cout << "Lib ";
            }
            ~Library() { cout << "~Lib "; }
            std::shared_ptr<Book> GetBook() const { return m_book; }
        private:
            std::shared_ptr<Book> m_book;
        };

        void Test()
        {
            // shared_ptr provides the same options for construction as unique_ptr.

            // Create an empty shared_ptr that initially does not point to anythig.
            auto p = std::shared_ptr<Book>{};

            assert(!p);
            
            cout << "cnt=" << p.use_count() << " "; // 0

            // You could write b.reset(new Book()) but it's more efficient to use make_shared.
            // The shared_ptr now points to an object.
            p = std::make_shared<Book>();

            assert(p != nullptr);

            cout << "cnt=" << p.use_count() << " "; // 1

            // Check if the shared_ptr is unique i.e., if its use_count is 1.
            assert(p.unique());

            // Copy the shared_ptr.
            auto pc = p;

            cout << "cnt=" << p.use_count() << " "; // 2

            // The pointer is no longer unique.
            assert(!p.unique());

            // Because the pointer is shared, the same assertions hold for the copied pointer. 
            cout << "cnt=" << pc.use_count() << " "; // 2
            assert(!pc.unique());

            // Copy the object being pointed to.
            Book copy = *p;

            // Get the reference.
            Book& ref = *p;

            // Get the raw pointer. Use it if you need to pass a resource to a C-style function. 
            Book* ptr = p.get();

            // Chak if the pointers point to the same object.
            assert(p.get() == pc.get());
            assert(p == pc); // the same as above

            std::shared_ptr<Book> b;

            {
                Library lib;
                b = lib.GetBook();  // the shared_ptr's reference counter is increased 
                                    // which prevents the Book from being destroyed when 
                                    // the Library goes out of scope

                Library lib2 = lib; // no copy ctor called on the Book member because it is shared between lib and lib2 (performance improvement)
                lib = lib2;         // no assigment operator called on the Book
            }

            // The library's only book does not get destroyed with the library because it is a shared_ptr.
            assert(b != nullptr);

            // You can write if(pn) and if(!pn) with smart pointers. 
            int n = 2;
            int* pn = nullptr;
            if (!pn) // conversion to bool
                pn = &n;
            if (pn) // conversion to bool
            { }
        }
    }


    //
    // weak_ptr
    //
    namespace WeakPtrExamples
    {
        void AssignSharedPtr()
        {
            auto sp = std::make_shared<int>(123);

            // Define an empty weak_ptr.
            auto wp = std::weak_ptr<int>{};

            // Assign a shared_ptr to a weak_ptr.
            wp = sp;
        }

        void InitWeakPtr()
        {
            auto sp = std::make_shared<int>(123);

            // Initialize a weak_ptr with a shared_ptr.
            auto wp = std::weak_ptr<int>{ sp };
        }

        void WeakPtrMembers()
        {
            auto sp = std::make_shared<int>(123);
            auto wp = std::weak_ptr<int>{ sp };

            // Use the expired() method to determine if there is any shared_ptr
            // pointing to an object. The weak_ptr is not expired since there 
            // is an outstanding shared_ptr.
            assert(!wp.expired());

            // Check if there is one strong reference.
            assert(wp.use_count() == 1);

            // Produce a new shared_ptr by locking the weak_ptr.
            if (auto locked = wp.lock()) // locked: [2 strong refs, 1 weak ref]
            {
                cout << "locked:" << *locked << " "; // 123

                // It's safe now to use the object being pointed to.
                // ...
            }

            // Reset the original shared_ptr.
            sp = nullptr; // sp is empty
            
            // At this point, the weak_ptr is expired but it still holds a weak reference.
            assert(wp.expired());

            // The use_count is now 0.
            assert(wp.use_count() == 0);

            // It's still safe to lock the weak_ptr but this time the lock method returns an empty 
            // shared_ptr and the if condition fails. In such case we should reset the weak_ptr. 
            if (auto locked = wp.lock()) // fails to convert weak_ptr to shared_ptr
            {
                cout << "locked:" << *locked << " "; // not executed
            }
            else
            {
                // Reset the weak_ptr. This releases the shared_ptr's control block. 
                wp.reset(); // wp is empty
            }
        }

        void Test()
        {
            AssignSharedPtr();
            InitWeakPtr();
            WeakPtrMembers();
        }
    }

    void Test()
    {
        UniquePtrExamples::Test();
        SharedPtrExamples::Test();
        WeakPtrExamples::Test();
    }
}
