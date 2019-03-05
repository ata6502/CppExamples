#include "AccountImpl.h"
#include <iostream>

using namespace Patterns;

using std::cout;

AccountImpl::AccountImpl(int v)
{
    m_v = v;
}

int AccountImpl::MyMethod()
{
    cout << m_v;
    return m_v;
}