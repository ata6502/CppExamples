#include "Account.h"
#include "AccountImpl.h"

#include <iostream>

using namespace Patterns;

// Account ctor delegates to pImpl ctor.
Account::Account(int v) : pImpl(new AccountImpl(v))
{
}

// We need destr in the .cpp file even if it's empty because
// the .cpp file has #include "AccountImpl.h" which includes 
// information about weather or not AccountImpl has a destr.
// This is a quirk of using a unique_ptr for pImpl.
Account::~Account()
{
}

Account::Account(Account&& otherAccount) : pImpl(std::move(otherAccount.pImpl))
{
}

Account& Account::operator=(Account&& otherAccount)
{
    pImpl = std::move(otherAccount.pImpl);
    return *this;
}

int Account::MyMethod()
{
    // Delegate to impl.
    return pImpl->MyMethod();
}

void Patterns::pImplTest()
{
    std::cout << "*** pImpl Pattern ***" << std::endl;

    Account a1(1); // a1.pImpl = unique_ptr { m_v = 1 }
    Account a2(2); // a2.pImpl = unique_ptr { m_v = 2 }

    // We move the accounts into the vector because the accounts are non-copyable.
    std::vector<Account> accounts;
    accounts.push_back(std::move(a1)); // a1.pImpl = empty
    accounts.push_back(std::move(a2)); // a2.pImpl = empty

    accounts[0].MyMethod(); // accounts[0].pImpl = unique_ptr { m_v = 1 }
    accounts[1].MyMethod(); // accounts[1].pImpl = unique_ptr { m_v = 2 }

    std::cout << std::endl;
}
