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
    - non-copyable (no copy ctor and no copy assignment operator)
    - can be moved (provides move ctor and move assignment); you can use std::move to move an object in and out of unique_ptr to transfer ownership of the object
    - works well in containers
    - use the make_unique function template to create and allocate objects to be owned by unique_ptr
      - make_ functions help to avoid explicit deletes
      - make_unique is a variadic template and relies on the standard forward helper function to ensure 
        that even user-defined types with non-trivial constructors may be constructed naturally and efficiently;
        this is sometimes called **perfect forwarding**
    - less overhead than shared_ptr
    - if an object is in a unique_ptr, you can give access to it through a raw pointer (the get method)
      - DO NOT control the object's lifetime through the raw pointer
      - test unique_ptr before calling get
    - use reset() to re-initialize the unique_ptr with a new value: ptr.reset(new MyClass()); 
      - the new object is created first and then the old object is cleaned up 
      - this saves you from self-assigment as well as from the case when the ctor throws an exception (the old object is still valid)
      - if you want to remove the old object first, just call reset with no parameters; this sets nullptr and clears up the object the pointer was pointing to
    - unique_ptr provides an explicit conversion to Boolean to determine whether it holds a non-null pointer

    shared_ptr
    - reference counted
    - shares the ownership of an object to which it points (implements shared ownership semantics)
    - non-invasive reference counting (shared_ptr wraps an object with a reference count); it means that you can add reference counting to any object without that object having to be aware of how it'll be allocated or shared
    - can be copied (provides a copy constructor and copy assignment)
    - can be moved (moving transfers the reference count owned by a shared_ptr without the cost of bumping up the reference count and then dropping it down; shared_ptr provides a move constructor and move assignment)
    - works well in containers
    - make_shared improves performance
    - use reset() to decrement the counter of a shared pointer and possibly delete it
    - you don't need the copy ctor and assignment operator to copy/assign the object that holds a shared_ptr
    - if an object is in a shared_ptr, give access to it through a weak_ptr
    - shared_ptr as well as unique_ptr provides the usual set of equallity and relational operators
    
    shared_ptr holds two pointers:
    - one to the object being managed
    - another one to the a control block
    
    The control block is a data structure that holds:
    - a strong ref count (strong use_count)
    - a weak ref count (weak use_count)
    - an optional deleter
    
    weak_ptr
    - originates from a shared_ptr and gives access to the pointed object
    - solves the problem of circular references in various data structures and object models
    - use it when you need to refer to an object managed by shared_ptr without taking a strong reference
    - shared_ptr along with weak_ptr provide a lightweight form of garbage collection

    When to use a pointer or a smart pointer:
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

    3. To allow shared access to an object on the free store. The object does not have a single owner.
       - Lifetime can be complicated to manage.

    4. Keep in mind that sometimes you have to use a shared_ptr even if you don't really want to or shouldn't have to. 
       Modern C++ containers can and generally do use an rvalue reference to move objects in and out of containers. 
       This enables you to create standard containers of unique_ptr. But some libraries fail to do so, in which case 
       you're left with either using raw pointer or shared_ptr. Raw pointer might be fine for scenario where you control 
       the lifetime of the container, but that's not always the case, certainly for concurrent systems. 

    You do not have to use smart pointers for everything. When you use a pointer to just observe, use a raw pointer.
    DO NOT control the object's lifetime through the raw pointer. Also, consider using references rather than pointers.
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

            // Wrap a raw pointer around a unique_ptr.
            auto* pb = new Book("C");
            // ... manipulate the Book object
            auto b6 = std::unique_ptr<Book>(pb);              // value: unique_ptr {m_title={"C"}}

            // Create a unique_ptr using the utility function make_unique.
            auto b = std::make_unique<Book>("D");             // value: unique_ptr {m_title={"D"}}

            // You are not able to copy an object that contains a unique_ptr
            // auto cb = b; // compiler error (C2280) - the copy ctor and the copy assignment are declared as 'delete'
            // auto cb(b);  // compiler error (C2280) - the same as above
        } // destr: ~D ~C ~B ~A

        void TransferObjectOwnership()
        {
            auto book1 = std::make_unique<Book>("E");

            // unique_ptr provides an explicit conversion to Boolean.
            if (book1) cout << "b1 "; // book1 owns a Book object

            // Use move semantics to transfer the object ownership from 
            // the unique_ptr on the right to the unique_ptr on the left.
            auto book2 = std::move(book1);

            if (book1) cout << "b1 "; // book1 does not own the Book object anymore
            if (book2) cout << "b2 "; // book2 owns the Book object
        } // Book destr is called only once


        // By using unique_ptr you can make the transfer of ownership in and out of a function explicit.

        // Transfer the ownership from a function.
        std::unique_ptr<Book> GetBook(const string& title)
        {
            // Return a pointer to a Book object.
            return std::make_unique<Book>(title);
        }

        // Transfer the ownership to a function. UpdateBook accepts a unique_ptr by value.
        // We need to move the object into the function explicitlyby using std::move.
        std::unique_ptr<Book> UpdateBook(std::unique_ptr<Book> book)
        {
            book->SetTitle("X");
            return book;
        }

        void UniquePtrMethods()
        {
            auto b = std::make_unique<Book>("F");

            // Create an independent copy of the owned object. Modifying the copy doesn't affect 
            // the object owned by the smart pointer and vice versa.
            Book copy = *b;

            // Get a reference of the object owned by unique_ptr.
            Book& ref = *b;

            // Get the pointer itself using the get method.
            Book* ptr = b.get();

            // Get the pointer and also release the ownership of it.
            Book* ptr2 = b.release(); // b is empty

            // Delete the owned object. 
            b.reset(); // at this point the unique_ptr no longer points to anything

            // Assume ownership of a raw pointer.
            b.reset(ptr); // now the unique_ptr owns the original Book object

            // Remarks: The above code is for illustration purposes only. You should always strive 
            // to pass raw or naked pointers directly between smart pointers rather than relying 
            // on intermediaries like ptr or ptr2. 

        } // Book destr called twice: ~F ~F


        // The BookWithPointer class has a unique_ptr member variable. 
        // Because it is a pointer the variable may be optional i.e. it 
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
            // If you want to make BookWithPointer non-copyable, make the copy ctor
            // and the copy assignment operator private:
            // Customer(const Customer&);
            // Customer& operator=(const Customer&);

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
                // You don't need to worry about the self-assignment.
                // unique_ptr takes care about it for you.
                m_author.reset(new Author());

                return *this;
            }

        private:
            string m_title;
            std::unique_ptr<Author> m_author;
        };

        void Test()
        {
            ConstructUniquePtr();
            TransferObjectOwnership();
            UniquePtrMethods();

            // Use a unique_ptr to return a heap-allocated variable from a function.
            {
                auto q = GetBook("Q");

                // Move the object in and out of the function explicitly.
                q = UpdateBook(std::move(q));
            }

            BookWithPointer p("P");
            BookWithPointer cp = p; // copy ctor
            p = cp; // copy assignment operator
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
            // shared_ptr provides much the same options for construction as unique_ptr.

            // Create an empty shared_ptr that initially does not point to anythig.
            auto p = std::shared_ptr<Book>{};

            // Assert b using the shared_ptr explicit Boolean conversion operator.
            assert(!p);
            
            cout << "cnt=" << p.use_count() << " "; // 0

            // We could write b.reset(new Book()) but it's more efficient to use make_shared.
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

            // Copy of the object being pointed to.
            Book copy = *p;

            // Get the reference. If we change the reference value, the change will be noticable by anyone sharing the object.
            Book& ref = *p;

            // Get the raw pointer. It's handy if we need to pass a resource to a C-style function. 
            Book* ptr = p.get();

            // Compare the pointers to determine whether they point to the same object.
            assert(p.get() == pc.get());
            assert(p == pc); // the same as above

            std::shared_ptr<Book> b;

            {
                Library lib;
                b = lib.GetBook(); // the shared_ptr's reference counter is increased 
                                   // which prevents the Book from being destroyed when 
                                   // the Library goes out of scope

                Library lib2 = lib; // no copy ctor called on the Book member because it is shared between lib and lib2 (performance improvement)
                lib = lib2; // no assigment operator called on the Book
            }

            // The library's only book does not get destroyed together with the library because it is a shared_ptr
            assert(b != nullptr);

            // nullptr - type safety
            // You can write if(pi) and if(!pi) with smart pointers. 
            int i = 2;
            int* pi = nullptr;
            if (!pi) // conversion to bool
                pi = &i;
            if (pi) // conversion to bool
            { }
        }
    }


    //
    // weak_ptr
    //
    namespace WeakPtrExamples
    {
        void AssignSharePtr()
        {
            auto sp = std::make_shared<int>(123);

            // Define an empty weak_ptr. We can assign it later a shared_ptr.
            auto wp = std::weak_ptr<int>{};

            // A usage pattern: 
            // when we have a shared_ptr in a data structure, we can then assign it to 
            // a weak_ptr in some other data structure to avoid a reference loop. 
            wp = sp;
        }

        void InitWeakPtr()
        {
            auto sp = std::make_shared<int>(123);

            // Initialize a weak_ptr with the shared_ptr.
            auto wp = std::weak_ptr<int>{ sp };
        }

        // convert the weak_ptr into a shared_ptr

        void WeakPtrMembers()
        {
            auto sp = std::make_shared<int>(123);
            auto wp = std::weak_ptr<int>{ sp };

            // Determine whether there is any shared_ptr pointing to a managed object using the expired() method.
            // The weak_ptr is not expired since there is an outstanding shared_ptr.
            assert(!wp.expired());

            // Get the strong reference use_count.
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

            // Similarly, the use_count is now 0.
            assert(wp.use_count() == 0);

            // It's still safe to lock the weak_ptr but this time the lock method returns an empty 
            // shared_ptr and the if condition fails. In such case we should reset the weak_ptr. 
            if (auto locked = wp.lock()) // fails to convert weak_ptr to shared_ptr
            {
                cout << "locked:" << *locked << " "; // not executed
            }
            else
            {
                // Reset the weak_ptr. The reason you might want to do this is because the weak_ptr,
                // once initialized with or assigned a shared_ptr, keeps the control block in memory.
                // The managed object is still destroyed, but the memory  allocation may linger until 
                // outstanding weak_ptr release their weak references to it. 
                wp.reset(); // wp is empty
            }
        }

        void Test()
        {
            AssignSharePtr();
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
