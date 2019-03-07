#pragma once

#include <windows.h>
#include "Diagnostics.h"

namespace KennyKerr
{
    template <typename Traits>
    class unique_handle
    {
        using pointer = typename Traits::pointer;

        pointer m_value;

        auto Close() throw() -> void
        {
            if (*this)
            {
                Traits::Close(m_value);
            }
        }

    public:

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

        auto operator=(unique_handle && other) throw() -> unique_handle &
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
        auto get() const throw() -> pointer
        {
            return m_value;
        }

        auto get_address_of() throw() -> pointer *
        {
            // Assert that this unique_handle doesn't currently own anything.
            // This way we cannot accidentally override any previously held resources.
            ASSERT(!*this);

            // Return the address of the underlying pointer. In this way, the caller 
            // receives a pointer to a pointer and can effectively place a value directly
            // into the unique_handle.
            return &m_value;
        }

        auto release() throw() -> pointer
        {
            auto value = m_value;
            m_value = Traits::Invalid();
            return value;
        }

        auto reset(pointer value = Traits::Invalid()) throw() -> bool
        {
            if (m_value != value)
            {
                Close();
                m_value = value;
            }

            return static_cast<bool>(*this);
        }

        auto swap(unique_handle<Traits> & other) throw() -> void
        {
            std::swap(m_value, other.m_value);
        }
    };

    template <typename Traits>
    auto swap(unique_handle<Traits> & left,
              unique_handle<Traits> & right) throw() -> void
    {
        left.swap(right);
    }

    template <typename Traits>
    auto operator==(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw() -> bool
    {
        return left.get() == right.get();
    }

    template <typename Traits>
    auto operator!=(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw() -> bool
    {
        return left.get() != right.get();
    }

    template <typename Traits>
    auto operator<(unique_handle<Traits> const & left,
                   unique_handle<Traits> const & right) throw() -> bool
    {
        return left.get() < right.get();
    }

    template <typename Traits>
    auto operator>=(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw() -> bool
    {
        return left.get() >= right.get();
    }

    template <typename Traits>
    auto operator>(unique_handle<Traits> const & left,
                   unique_handle<Traits> const & right) throw() -> bool
    {
        return left.get() > right.get();
    }

    template <typename Traits>
    auto operator<=(unique_handle<Traits> const & left,
                    unique_handle<Traits> const & right) throw() -> bool
    {
        return left.get() <= right.get();
    }

    struct null_handle_traits
    {
        using pointer = HANDLE;

        static auto Invalid() throw() -> pointer
        {
            return nullptr;
        }

        static auto Close(pointer value) throw() -> void
        {
            VERIFY(CloseHandle(value));
        }
    };

    struct invalid_handle_traits
    {
        using pointer = HANDLE;

        static auto Invalid() throw() -> pointer
        {
            return INVALID_HANDLE_VALUE;
        }

        static auto Close(pointer value) throw() -> void
        {
            VERIFY(CloseHandle(value));
        }
    };

    using null_handle = unique_handle<null_handle_traits>;
    using invalid_handle = unique_handle<invalid_handle_traits>;
}
