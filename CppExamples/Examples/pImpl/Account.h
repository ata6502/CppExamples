#pragma once

#include <memory>
#include <vector>

// When the pImpl idiom is used, changes in AccountImpl do not trigger recompilation
// of files that #include Account.h

namespace Patterns
{
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
        // Forward declaration
        //
        // AccountImpl is declared as a private nested class. Use a public nested
        // implementation class only if other classes or functions need to access
        // the implementation class members.
        class AccountImpl;

        // unique_ptr makes the class non-copyable.
        std::unique_ptr<AccountImpl> pImpl;
    };

    void pImplTest();
}
