#pragma once

#ifdef _DEBUG
    #include <crtdbg.h>
    #define ASSERT _ASSERTE
#else
    #define ASSERT __noop
#endif

namespace KennyKerr
{
    // unique_handle is a traits class.
    template <typename Traits>
    class unique_handle
    {
        using pointer = typename Traits::pointer;

        pointer m_value;

        // An invalid handle. Any concrete traits class is free
        // to override it.
        static pointer Invalid() noexcept
        {
            return nullptr;
        }

        void Close() throw()
        {
            if (*this)
            {
                Traits::Close(m_value);
            }
        }

    public:

        // Delete the copy ctor and copy assignment operator.
        unique_handle(unique_handle const &) = delete;
        auto operator=(unique_handle const &) -> unique_handle & = delete;

        explicit unique_handle(pointer value = Traits::Invalid()) throw() :
            m_value { value }
        {
        }

        unique_handle(unique_handle && other) throw() :
            m_value { other.release() }
        {
        }

        unique_handle& operator=(unique_handle && other) throw()
        {
            if (this != &other)
            {
                reset(other.release());
            }

            return *this;
        }

        ~unique_handle() throw()
        {
            Close();
        }

        explicit operator bool() const throw()
        {
            return m_value != Traits::Invalid();
        }

        // get() returns the underlying pointer or handle.
        pointer get() const throw()
        {
            return m_value;
        }

        pointer* get_address_of() throw()
        {
            // Assert that this unique_handle doesn't currently own anything.
            // This way we cannot accidentally override any previously held resources.
            ASSERT(!*this);

            // Return the address of the underlying pointer. In this way, the caller 
            // receives a pointer to a pointer and can effectively place a value directly
            // into the unique_handle.
            return &m_value;
        }

        // release() detaches the ownership of a handle.
        pointer release() throw()
        {
            auto value = m_value;
            m_value = Traits::Invalid();
            return value;
        }

        // reset() attaches a handle even if the existing handle is owned.
        bool reset(pointer value = Traits::Invalid()) throw()
        {
            if (m_value != value)
            {
                Close();
                m_value = value; // assume ownership
            }

            // Useful for validity checks.
            return static_cast<bool>(*this);
        }

        void swap(unique_handle<Traits> & other) throw()
        {
            pointer tmp = m_value;
            m_value = other.m_value;
            other.m_value = tmp;
        }
    };

    // non-member swap function.
    template <typename Traits>
    void swap(unique_handle<Traits> & left,
              unique_handle<Traits> & right) throw()
    {
        left.swap(right);
    }

    template <typename Traits>
    bool operator==(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw()
    {
        return left.get() == right.get();
    }

    template <typename Traits>
    bool operator!=(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw()
    {
        return left.get() != right.get();
    }

    template <typename Traits>
    bool operator<(unique_handle<Traits> const & left,
                   unique_handle<Traits> const & right) throw()
    {
        return left.get() < right.get();
    }

    template <typename Traits>
    bool operator>=(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw()
    {
        return left.get() >= right.get();
    }

    template <typename Traits>
    bool operator>(unique_handle<Traits> const & left,
                   unique_handle<Traits> const & right) throw()
    {
        return left.get() > right.get();
    }

    template <typename Traits>
    bool operator<=(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw()
    {
        return left.get() <= right.get();
    }
}
