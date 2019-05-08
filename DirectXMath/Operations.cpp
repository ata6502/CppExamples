#include <iostream>

#include "OutputOperators.h"
#include "Operations.h"

using namespace DirectX;

using std::cout;
using std::endl;

void ArithmeticOperations()
{
    cout.precision(4);

    XMVECTOR v, v1, v2;

    // Compute the absolute value of each component of a vector.
    v = XMVectorSet(-1.5f, 2.8f, -5.0f, 3.0f);
    cout << XMVectorAbs(v) << endl; // (1.5, 2.8, 5.0, 3.0)

    // Compute the cosine of each component of a vector.
    v = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);
    cout << XMVectorCos(v) << endl; // (1.0, 0.7071, -1.192e-007, -1.0)

    // Compute the base two logarithm of each component of a vector.
    v = XMVectorSet(1.0f, 2.0f, 4.0f, 8.0f);
    cout << XMVectorLog2(v) << endl; // (0, 1, 2, 3)

    // Compute two raised to the power for each component of a vector.
    v = XMVectorSet(2.0f, 3.0f, 4.0f, 5.0f);
    cout << XMVectorExp2(v) << endl; // (4, 8, 16, 32)

    // Return a vector where each component is the corresponding component 
    // of v1 raised to the power of the corresponding component of v2.
    v1 = XMVectorSet(2.0f, 3.0f, 4.0f, 5.0f);
    v2 = XMVectorSet(4.0f, 3.0f, 2.0f, 1.0f);
    cout << XMVectorPow(v1, v2) << endl; // (16, 27, 16, 5)

    // Compute the square root for each component of a vector.
    v = XMVectorSet(121.0f, 256.0f, 4.0f, 27.0f);
    cout << XMVectorSqrt(v) << endl; // (11, 16, 2, 5.196)

    cout << endl;
}

void Swizzling()
{
    // XMVECTOR XMVectorSwizzle(XMVECTOR V, uint E0, uint E1, uint E2, uint E3)
    // V - Vector to swizzle.
    // E0 - Index that describes which component of V to place in the x-component of the swizzled vector. 
    // E1 - Index that describes which component of V to place in the y-component of the swizzled vector. 
    // E2 - Index that describes which component of V to place in the z-component of the swizzled vector. 
    // E3 - Index that describes which component of V to place in the w-component of the swizzled vector. 
    XMVECTOR v = XMVectorSet(5.0f, 8.0f, 10.0f, 20.0f);
    cout << XMVectorSwizzle(v, 0, 0, 1, 1) << endl; // (5, 5, 8, 8) 
    cout << XMVectorSwizzle(v, 3, 3, 0, 2) << endl; // (20, 20, 5, 10)
    cout << XMVectorSwizzle(v, 2, 1, 2, 3) << endl; // (10, 8, 10, 20)

    cout << endl;
}

void AngleConversion()
{
    cout.precision(9);

    // inline float XMConvertToRadians(float fDegrees) { return fDegrees * (XM_PI / 180.0f); }
    // inline float XMConvertToDegrees(float fRadians) { return fRadians * (180.0f / XM_PI); }

    cout << XMConvertToRadians(90.f) << endl;
    cout << XMConvertToDegrees(XM_PIDIV2) << endl;

    cout << endl;
}

void MinMax()
{
    cout.precision(4);

    // template<class T> inline T XMMin(T a, T b) { return (a < b) ? a : b; }
    // template<class T> inline T XMMax(T a, T b) { return (a > b) ? a : b; }

    // MSDN: Use std::min instead of XMMin. To avoid conflicts with Windows headers with std::min, you need to #define NOMINMAX before you include Windows headers.

    cout << XMMin(2.3f, 2.1f) << endl;
    cout << XMMax(2.3f, 2.1f) << endl;

    cout << endl;
}

void Constants()
{
    cout.precision(9);

    /*
    const float XM_PI           = 3.141592654f;
    const float XM_2PI          = 6.283185307f;
    const float XM_1DIVPI       = 0.318309886f;
    const float XM_1DIV2PI      = 0.159154943f;
    const float XM_PIDIV2       = 1.570796327f;
    const float XM_PIDIV4       = 0.785398163f;
    */

    cout << XM_PI << endl;
    cout << XM_2PI << endl;
    cout << XM_1DIVPI << endl;
    cout << XM_1DIV2PI << endl;
    cout << XM_PIDIV2 << endl;
    cout << XM_PIDIV4 << endl;

    cout << endl;
}

