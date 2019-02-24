#pragma once

#include <iostream>
#include <utility> // std::move, std::swap (non-member function)
#include <algorithm> // std:swap (the standard algorithm template)
#include <memory> // unique_ptr, shared_ptr, weak_ptr
#include "Diagnostics.h" // ASSERT, VERIFY, TRACE

using std::cout;
using std::cerr;
using std::endl;

/*
    Smart classes manage resources efficiently
    ==========================================

    Smart classes are usually defined as templates.

    A handle wrapper - a class template for managing a resource whose lifetime is controlled by a handle. 
    This is a common approach used by C-style APIs, even for modern APIs where binary probability is required. 
    Handles indirectly refer to objects. 
    
    Rather than calling virtual functions we call standalone or non-member functions providing each call 
    with a handle to the object in question:
    
    auto h = HANDLE { CreateEvent(...) };
    SetEvent(h);
    CloseHandle(h);
    
    The handles often refer to kernel objects, meaning they are defined by a block of memory inside the kernel 
    and exposed indirectly to applications in user mode. Others live entirely in your applications address space, 
    but usually have some indirect or lazy association with one or more kernel objects. Behind the scenes these 
    objects often employ reference counting, but a handle tends to be regarded as an exclusive resource that 
    an application manages and then closes implicitly releasing the reference to the object. 
    
    Think of a handle as an opaque pointer to an object, it's not necessarily a pointer. It might just be a unique 
    identifier within the process or system. Either way you cannot manipulate these handles directly. 
*/

namespace SmartClassesExamples
{
    // The unique handle class template is a resource manager. It aims 
    // to provide safe and efficient ownership of some resource. 
    // The unique_handle reflects the semantics of handle management. 
    // The class holds a "unique" handle because handles usually do not support 
    // duplication or sharing.
    // Our unique_handle class needs more than just the handle type so we provide a Traits class.
    template <typename Traits>
    class unique_handle
    {
        typedef typename Traits::pointer pointer; // use the 'typename' keyword to tell the compiler that Traits::pointer is the name of a type

    public:

        // We defined the ctor as explicit to avoid default conversions. By default, a single argument 
        // ctor acts as an implicit conversion. Implicit operations are dangerous in resource managers 
        // and can often lead to performance problems. 
        // The default constructed unique_handle starts off empty. 
        explicit unique_handle(pointer value = Traits::invalid()) noexcept
            : m_value{ value }
        {
        }

        // The move ctor. Move operations take rvalue references. Also, move operations mustn't throw
        // an exception. We call the release method to implement our move ctor: we intialize the member
        // variable m_value with what was returned or yielded by the other unique handle. In that way,
        // we're effectively moving ownership of the handle from one unique_handle to another as part 
        // of construction. 
        unique_handle(unique_handle&& other) noexcept
            : m_value{ other.release() }
        {
        }

        // The move assignment operator. 
        unique_handle& operator=(unique_handle&& other) noexcept
        {
            // Prevent the object from moving some value onto itself.
            if (this != &other)
            {
                // Move the handle from the other unique_handle using the reset method
                // to ensure that any existing handle is first closed.
                reset(other.release());
            }

            return *this;
        }

        // Destr closes the handle by calling the close() method. That's why the close() method
        // is not allowed to throw exceptions.
        ~unique_handle() noexcept
        {
            close();
        }

        // The explicit Boolean conversion operator.
        explicit operator bool() const noexcept
        {
            // Return true if the handle is valid or false if not.
            return m_value != Traits::invalid();
        }

        // The get() method returns the underlying (owned) raw handle.
        pointer get() const noexcept
        {
            return m_value;
        }

        // The release() method frees its ownership of the pointer (i.e., the handle)
        // and returns its original value . It useful when we want to transfer the ownership 
        // of the handle out of the unique_handle.
        pointer release() noexcept
        {
            // Keep the original value of the handle in a temporary variable.
            auto value = m_value;

            // Invalidate the handle.
            m_value = Traits::invalid();

            // Return the original value of the handle.
            return value;
        }

        // The reset() method replaces the owned handle with another (possibly invalid) handle.
        // If the unique_handle owns a handle, reset() ensures the handle is first closed. 
        // Returns true if the unique_handle remains valid after reset.
        bool reset(pointer value = Traits::invalid()) noexcept
        {
            // Check if we try to assign the same handle.
            if (m_value != value)
            {
                // If the handle is different, close the existing handle.
                close();

                // Assume the ownership of the new handle.
                m_value = value;
            }

            // Call the explicit Boolean conversion operator as the result.
            return static_cast<bool>(*this);
        }

        // An efficient swap operation. We swap the handle values with no additional overhead.
        // We also need to define a non-member swap function to tell the compiler that unique_handle has a swap member function.
        void swap(unique_handle<Traits>& other) noexcept
        {
            //TRACE(L"swap\n");

            // Use the standard swap algorithm.
            std::swap(m_value, other.m_value);
        }

        // Make unique_handle non-copyable.
        unique_handle(unique_handle const &) = delete; // remove copy ctor
        unique_handle& operator=(unique_handle const &) = delete; // remove copy assignment operator

    private:
        pointer m_value; // holds the HANDLE value

        // close() is a helper method that closes the handle using the Traits class provided as the template parameter. 
        void close() noexcept
        {
            // Determine whether the unique_handle is valid using the explicit Boolean conversion operator.
            if (*this)
            {
                // If it is, close the handle.
                Traits::close(m_value);
            }
        }
    };

    // The non-member swap function template tells the compiler that the unique_handle has a swap member function.
    // The template advertises the fact that the unique_handle class provides its own swap implementation 
    // that should be used when swapping unique_handles.
    template <typename Traits>
    void swap(
        unique_handle<Traits>& left,
        unique_handle<Traits>& right) noexcept
    {
        // Forward the request to the member function that implements the swap operation most efficiently. 
        left.swap(right);
    }

    // Operator functions make it easier to use our own types within containers. 
    // We can define operators as member or non-member functions. It's usually best to use a non-member. 
    // At a minimum you should consider supporting equality and the basic set of relational operators. 
    
    // The euqlity operator may be used to determine whether a give handle is present in a sequence or 
    // to find the first empty handle.
    template <typename Traits>
    bool operator==(unique_handle<Traits> const & left,
        unique_handle<Traits> const & right) noexcept
    {
        // Compare the underlying handle values.
        return left.get() == right.get();
    }

    template <typename Traits>
    bool operator!=(unique_handle<Traits> const & left,
        unique_handle<Traits> const & right) noexcept
    {
        return left.get() != right.get();
    }

    template <typename Traits>
    bool operator<(unique_handle<Traits> const & left,
        unique_handle<Traits> const & right) noexcept
    {
        return left.get() < right.get();
    }

    template <typename Traits>
    bool operator>=(unique_handle<Traits> const & left,
        unique_handle<Traits> const & right) noexcept
    {
        return left.get() >= right.get();
    }

    template <typename Traits>
    bool operator>(unique_handle<Traits> const & left,
        unique_handle<Traits> const & right) noexcept
    {
        return left.get() > right.get();
    }

    template <typename Traits>
    bool operator<=(unique_handle<Traits> const & left,
        unique_handle<Traits> const & right) noexcept
    {
        return left.get() <= right.get();
    }

    // Specialized traits classes are used to distinguish or describe different handled types.

    struct null_handle_traits
    {
        // The HANDLE is our logical pointer - it points to an object.
        typedef HANDLE pointer;

        // Define the validity of the null_handle_traits class.
        // The invalid() method returns the value of an invalid handle.
        static constexpr pointer invalid() noexcept
        {
            return nullptr; 
        }

        // The close() method closes the handle.
        static void close(pointer value) noexcept
        {
            VERIFY(CloseHandle(value));
        }
    };

    struct invalid_handle_traits
    {
        typedef HANDLE pointer;

        // The value of an invalid handle as reported by the CreateFile 
        // function is the INVALID_HANDLE_VALUE constant. 
        static constexpr pointer invalid() noexcept
        {
            return INVALID_HANDLE_VALUE; // -1
        }

        // The CreateFile function returns a handle to a standard kernel 
        // object so the CloseHandle function takes care of closing the handle. 
        static void close(pointer value) noexcept
        {
            VERIFY(CloseHandle(value));
        }
    };

    // The aliases (typedefs) for the traits classes.
    typedef unique_handle<null_handle_traits> null_handle;
    typedef unique_handle<invalid_handle_traits> invalid_handle;

    void InitHandle()
    {
        // Keep a handle returned from CreateEvent in a unique_handle. 
        auto event = null_handle
        {
            CreateEvent(nullptr,  // a default security descriptor
                        true,     // a manual reset event
                        false,    // initially non-signaled
                        nullptr)  // without a name
        };

        // If the handle is valid, signal the event.
        if (event)
        {
            VERIFY(SetEvent(event.get())); // grab the raw handle using the get method
        }
    } // the unique_handle destr closes the handle

    void ReleaseHandle()
    {
        auto event = null_handle{ CreateEvent(nullptr, true, false, nullptr) };

        // A potentially dangerous way of transfering the ownership.
        HANDLE danger = event.release();

        //...

        // We need to close the handle ourselves because we own the handle.
        VERIFY(CloseHandle(danger));

    } // the unique_handle destr is no longer responsible for the handle

    void ResetHandle()
    {
        auto event = null_handle{ CreateEvent(nullptr, true, false, nullptr) };

        // Replace the event object with a new object. 
        if (event.reset(CreateEvent(nullptr, false, false, nullptr)))
        {
            cout << "'New handle is valid' ";
        }

        // You could also just close the handle without replacing it with a new object.
        //event.reset();

    } // the unique_handle destr closes the handle of the new event object

    // There's only one unique_handle that owns the handle at any given moment and 
    // only one of the destructors closes the handle. 
    void MoveHandle()
    {
        auto event = null_handle{ CreateEvent(nullptr, true, false, nullptr) };

        // event is initially valid.
        ASSERT(event);

        // Turn the event object into an rvalue by passing the event to the move function.
        auto other = null_handle{ std::move(event) };

        
        // At this point, the event is no longer valid since the other unique handle has taken over.
        ASSERT(!event);
        ASSERT(other);

        // Move the handle back to the original unique_handle.
        event = std::move(other);

        // The event is valid again and the other handle is not valid.
        ASSERT(event);
        ASSERT(!other);
    }

    void SwapHandles()
    {
        auto first = null_handle{ CreateEvent(nullptr, true, false, nullptr) };
        auto second = null_handle{};

        // The generic swap.
        std::swap(first, second);
    }


    void ArgumentDependentLookup()
    {
        auto first = std::make_unique<int>(1);
        auto second = std::make_unique<int>(2);

        // The std qualification for swap is unnecessary. If the compiler doesn't find a swap function 
        // in the current namespace, it searches for one in the namespaces of its arguments.
        // The arguments in this case are both in the std namespace and so the compiler finds the swap function there. 
        // The following function is not the generic swap function template used in SwapHandles. 
        // This is a version specialized for unique pointers that swaps pointers.
        swap(first, second);
    }

    // EfficientSwapping uses specialized swap functions.
    void EfficientSwapping()
    {
        // An array of 10 handles.
        null_handle handles[10];

        // Five calls to the efficient swap member function - no temporary objects, no move assignments, and no constructors or destructors.
        std::reverse(std::begin(handles), std::end(handles));
    }




    //
    // File Mapping Demo (invalid_handle)
    //

    // This demo illustrates how to use the unique_handle class template to perform a file mapping operation on Windows. 
    // One the simplest and most efficient ways of reading the entire file is to map it into the address space of 
    // the calling process. This takes advantage of the OS virtual memory manager and file system cache to provide 
    // incredible performance. The trick is that you need to combine the file management API with a memory management API. 
    
    // We manage the following resources:
    // - the file object
    // - the file mapping object
    // - the mapped view which must be unmapped to free the chain of resources
    
    // A deleter used with unique_pointer to unmap a file.
    struct map_view_deleter
    {
        // A pointer type required by the UnmapViewOfFile function.
        typedef char const * pointer;

        void operator()(pointer value) const noexcept
        {
            VERIFY(UnmapViewOfFile(value));
        }
    };

    // FileMappingDemo opens a file and prints it out to the console. 
    void FileMappingDemo()
    {
        // Use a Unicode raw string literal to avoid a sequence of escape characters.
        auto filename = LR"(C:\Projects\Cpp\CppExamples\smart_classes.dat)";

        // Define a file object as an invalid_handle and initialize it with a CreateFile function
        // from the file management API.
        // The CreateFile function returns a handle to a file object, but for historical 
        // reasons the value returned on failure is something other than a null pointer value (INVALID_HANDLE_VALUE).
        // We use the invalid_handle handle traits class to accommodate this.
        auto file = invalid_handle
        {
            CreateFile(filename,                // the name of the file to open
                       GENERIC_READ,            // the desired access rights, we're going to read the contents
                       FILE_SHARE_READ,         // the share mode, we don't want anyone to modify the file while we're reading it
                       nullptr,                 // a default security descriptor
                       OPEN_EXISTING,           // open an existing file rather than creating or truncating an existing file
                       FILE_ATTRIBUTE_NORMAL,   // no need for any special semantics
                       nullptr)                 // the optional template, not used with opening a file
        };

       
        // Rely on the explicit Boolean conversion operator to check for failure.
        if (!file)
        {
            // The file management and memory management API uses the GetLastError function to 
            // provide an error code for the last reported failure within the current context. 
            cerr << "CreateFile failed: " << GetLastError();
            return;
        }

        // Check if the file is empty. If that's the case then we won't be able to map it. 
        // The GetFileSizeEx function returns the size of the file as a 64-bit large integer structure. 
        // This is a union to support compilers that didn't have a build in 64-bit integer type. 
        
        auto size = LARGE_INTEGER{};

        // The GetFileSizeEx function may fail although it's unlikely since the file is now 
        // locked by the process.
        if (!GetFileSizeEx(file.get(), &size))
        {
            cerr << "GetFileSizeEx failed: " << GetLastError();
            return;
        }

        // Check if the file is not empty. We know it isn't in this case, but it's a good habit
        // because we cannot map an empty file with the CreateFileMapping function.
        if (size.QuadPart == 0)
        {
            cerr << "File is empty";
            return;
        }

        // Unlike the CreateFile function, the CreateFileMapping function reports failure with a null pointer value. 
        // That's why we use the null_handle instead of invalid_handle.
        auto map = null_handle
        {
            CreateFileMapping(file.get(),       // get the file handle
                              nullptr,          // the default security descriptor
                              PAGE_READONLY,    // the way in which memory pages are secured by the memory manager
                              0,0,              // the high and low order words reflecting the file size; we just let the CreateFileMapping function retrieve this from the file itself
                              nullptr)          // no name for the file mapping object since we don't share it
        };

        if (!map)
        {
            cerr << "CreateFileMapping failed: " << GetLastError();
            return;
        }

        // Keep in mind that the file mapping object maintains a reference to the file object. 
        // We could reset our file object here to close the handle. This is unnecessary in this 
        // case since the unique_handle destructor will eventually close it for us but there's 
        // no need to keep the file handle open. 
        file.reset();

        // At this point we have:
        // - a file object
        // - a file mapping object
        
        // Map a view of the file into memory using the MapViewOfFile function. The function returns an actual pointer - 
        // the starting address of a sequence of pages representing the contents of the file mapped into the calling process. 
        // We use the unique_ptr to manage this resource. We initialize it with the results of MapViewOfFile.
        // We also need a deleter class for unmapping as it involves another API function. 
        auto view = std::unique_ptr<char, map_view_deleter>
        {
            static_cast<char *>(MapViewOfFile(map.get(),        // the handle of the file mapping object
                                              FILE_MAP_READ,    // limit the page protection as needed
                                              0,0,              // the offset into the file mapping object where the map view should begin (a high and low order words for the 64-bit offset)
                                              0))               // the number of bytes to map; we allow the function to ensure that the mapping extends from the offset to the end of the file mapping
        };

        if (!view)
        {
            cerr << "MapViewOfFile failed: " << GetLastError();
            return;
        }

        // Print out the contents of the file.
        cout << static_cast<unsigned>(size.QuadPart) << ":" << view.get() << " ";
    }
    
    void Test()
    {
        // null_handle
        InitHandle();
        ReleaseHandle();
        ResetHandle();
        MoveHandle();
        SwapHandles();
        ArgumentDependentLookup();
        EfficientSwapping();

        // invalid_handle
        FileMappingDemo();
    }
}