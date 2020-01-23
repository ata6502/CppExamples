#pragma once

namespace Patterns
{
    class AccountImpl
    {
    public:
        AccountImpl(int v);
        int MyMethod();

    private:
        // ... implementation details
        int m_v;
    };
}
