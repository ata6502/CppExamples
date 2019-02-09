#pragma once

#include <memory>
#include <vector>

// When the pImpl idiom is used, no change in AccountImpl triggers recompilation
// of Main or any other files that #include Account.h

namespace Patterns
{
    // Just the forward declaration, not #include "AccountImpl.h"
    class AccountImpl;

    class Account
    {
    public:
        Account(int v);
        ~Account();
        int MyMethod();

        // moving is ok, copying is not (unless you implement deep copy)
        Account(Account&& otherAccount);
        Account& operator=(Account&& otherAccount);

    private:
        // A unique_ptr member makes the class non-copyable.
        std::unique_ptr<AccountImpl> pImpl;
    };

    void pImplTest();
}
