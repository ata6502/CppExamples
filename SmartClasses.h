#pragma once

#include "Diagnostics.h"

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

    // Trait classes are used to distinguish or describe different handled types. 
    // Here, we define a null_handle_traits class.
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

    // Define a null handle.
    typedef unique_handle<null_handle_traits> null_handle;

    void InitHandleToNull()
    {
        // Initialize a raw handle.
        auto raw = HANDLE{ nullptr };

        // TODO: Use move semantics.
        /*
        // Initialize a null_handle. The default ctor accepts the pointer type.
        auto h = null_handle{ raw };

        // Determine whether the handle is valid using the explicit Boolean conversion operator.
        if (h)
        {
            // ... not executed because the unique_handle is invalid
        }
        */
    }

    void InitHandleToValue()
    {
        // TODO: Use move semantics.
        /*
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
        */
    } // the unique_handle destr closes the handle

    void ReleaseHandle()
    {
        // TODO: Use move semantics.
        /*
        auto event = null_handle{ CreateEvent(nullptr, true, false, nullptr) };

        // A potentially dangerous way of transfering the ownership.
        HANDLE danger = event.release();

        //...

        // Close the handle ourselves because we own the handle.
        VERIFY(CloseHandle(danger));
        */

    } // the unique_handle destr is no longer responsible for the handle

    void ResetHandle()
    {
        // TODO: Use move sematics.
        /*
        auto event = null_handle{ CreateEvent(nullptr, true, false, nullptr) };

        // Replace the event object with a new object. 
        if (event.reset(CreateEvent(nullptr, false, false, nullptr)))
        {
            cout << "'New handle is valid' ";
        }
        */

        // You could also just close the handle without replacing it with a new object.
        //event.reset();

    } // the unique_handle destr closes the handle of the new event object

    void Test()
    {
        InitHandleToNull();
        InitHandleToValue();
        ReleaseHandle();
        ResetHandle();
    }
}