#include <iostream>
#include <DirectXPackedVector.h>

#include "OutputOperators.h"
#include "Vectors.h"

using namespace DirectX;

using std::cout;
using std::endl;

/*
XMVectorSet: (1.1, 2.2, 3.3, 0)
XMVectorZero: (0, 0, 0, 0)
XMVectorSplatOne: (1, 1, 1, 1)
XMVectorReplicate: (-1, -1, -1, -1)
XMVectorSplatZ: (3, 3, 3, 3)
*/
void VectorSetters()
{
    // C++ 11 initialization syntax. 
    // MSDN: Do not use initializer lists directly with XMVECTOR (that is, XMVECTOR v = { 1.0f, 2.0f, 3.0f, 4.0f }). 
    // Such code is inefficient and is not portable across all platforms that are supported by DirectXMath.
    const XMVECTORF32 v = { 1.f, 2.f, 3.f, 0.f };

    // Initialization
    cout << XMVectorSet(1.1f, 2.2f, 3.3f, 4.4f) << endl;
    cout << XMVectorZero() << endl;
    cout << XMVectorSplatOne() << endl;
    cout << XMVectorReplicate(-1.0f) << endl;
    cout << XMVectorSplatX(v) << endl;
    cout << XMVectorSplatY(v) << endl;
    cout << XMVectorSplatZ(v) << endl;

    // Accessors - read a single component of XMVECTOR.
    cout << XMVectorGetX(v) << endl;
    cout << XMVectorGetY(v) << endl;
    cout << XMVectorGetZ(v) << endl;
    cout << XMVectorGetW(v) << endl;

    // Mutators - write to a single component of XMVECTOR.
    cout << XMVectorSetX(v, 11.0f) << endl;
    cout << XMVectorSetY(v, 22.0f) << endl;
    cout << XMVectorSetZ(v, 33.0f) << endl;
    cout << XMVectorSetW(v, 44.0f) << endl;

    // ??? These functions do not make any sense.
    // They accept uint and then cast internally to float.

    // Load 3-element unit array into XMVECTOR.
    uint32_t a[3] = { 3U, 2U, 1U };
    XMVECTOR vo = DirectX::XMLoadInt3(a); // vo = garbage

    // Load XMVECTOR into 3 element unit array.
    DirectX::XMStoreInt3(a, v); // a = garbage
}

// XMFLOAT --> XMVECTOR
void VectorLoading()
{
    // XMFLOAT2, XMFLOAT3, XMFLOAT4 are usually class members
    // XMVECTOR is a SIMD type

    XMVECTOR v;

    // Load XMFLOAT2 into XMVECTOR.
    XMFLOAT2 f2 = XMFLOAT2(1.1f, 2.8f);
    v = XMLoadFloat2(&f2); // v = (1.1, 2.8, 0, 0)
    cout << v << endl;

    // Load XMFLOAT3 into XMVECTOR.
    XMFLOAT3 f3 = XMFLOAT3(2.3f, 3.4f, 1.6f);
    v = XMLoadFloat3(&f3); // v = (2.3, 3.4, 1.6, 0)
    cout << v << endl;

    // Load XMFLOAT4 to XMVECTOR
    XMFLOAT4 f4 = XMFLOAT4(3.5f, 2.3f, 5.1f, 7.4f);
    v = XMLoadFloat4(&f4); // v = (3.5, 2.3, 5.1, 7.4)
    cout << v << endl;
}

// XMVECTOR --> XMFLOAT
void VectorStoring()
{
    // XMFLOAT2, XMFLOAT3, XMFLOAT4 are usually class members
    // XMVECTOR is a SIMD type

    XMVECTOR v = XMVectorSet(1.0f, 2.0f, 3.0f, 4.0f);

    // Store XMVECTOR in XMFLOAT2.
    XMFLOAT2 f2;
    XMStoreFloat2(&f2, v); // f2 = (1, 2)
    cout << f2 << endl;

    // Store XMVECTOR in XMFLOAT3.
    XMFLOAT3 f3;
    XMStoreFloat3(&f3, v); // f3 = (1, 2, 3)
    cout << f3 << endl;

    // Store XMVECTOR in XMFLOAT4.
    XMFLOAT4 f4;
    XMStoreFloat4(&f4, v); // f4 = (1, 2, 3, 4)
    cout << f4 << endl;

    // Store XMVECTOR in XMFLOAT3 using a helper function.
    XMFLOAT3 f = VectorToFloat3(v);
    cout << f << endl; // f = (1, 2, 3)
}

void ConstVectors()
{
    // Constant XMVECTOR instances should use the XMVECTORF32 or XMVECTORU32 types.
    // These types are 16-byte aligned structures with a XMVECTOR() conversion operator.

    const XMVECTORF32 v = { 1.0f, 2.0f, 3.0f, 8.0f };
    const XMVECTORF32 halfVector = { 0.5f, 0.5f, 0.5f, 0.5f };
    const XMVECTORF32 zeroVector = { 0.0f, 0.0f, 0.0f, 0.0f };
    const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
    const XMVECTORU32 uvec = { 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000 };
}

void VectorOperators()
{
    XMVECTOR u = XMVectorSet(2.0f, 1.5f, 3.2f, 0.0f);
    XMVECTOR v = XMVectorSet(-1.0f, 3.0f, -2.0f, 0.0f);

    // XMVECTOR operator- (FXMVECTOR V)
    cout << "-v = " << -v << endl;

    // XMVECTOR operator+ (FXMVECTOR V1, FXMVECTOR V2)
    cout << "u+v = " << u + v << endl;

    // XMVECTOR operator- (FXMVECTOR V1, FXMVECTOR V2)
    cout << "u-v = " << u - v << endl;

    // XMVECTOR operator* (float S, FXMVECTOR V)
    cout << "8*u = " << 8.0f*u << endl;

    // XMVECTOR operator* (FXMVECTOR V, float S);
    cout << "u*8 = " << u*8.0f << endl;

    // Other operators
    /*
    XMVECTOR& operator+= (XMVECTOR& V1, FXMVECTOR V2);
    XMVECTOR& operator-= (XMVECTOR& V1, FXMVECTOR V2);
    XMVECTOR& operator*= (XMVECTOR& V1, FXMVECTOR V2);
    XMVECTOR& operator/= (XMVECTOR& V1, FXMVECTOR V2);

    XMVECTOR& operator*= (XMVECTOR& V, float S);
    XMVECTOR& operator/= (XMVECTOR& V, float S);

    XMVECTOR operator* (FXMVECTOR V1, FXMVECTOR V2);
    XMVECTOR operator/ (FXMVECTOR V1, FXMVECTOR V2);
    XMVECTOR operator/ (FXMVECTOR V, float S);
    */
}

void VectorFunctions()
{
    // DirectXMath provides 2D, 3D, and 4D vector functions.
    // The functions that return a scalar replicate the value across each of the XMVECTOR components.

    // Test vectors.
    XMVECTOR v = XMVectorSet(3.4641f, 3.0f, 2.0f, 0.0f);
    XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);

    // The following functions return XMVECTOR.
    /*
    ||v||     = (5, 5, 5, 5)
    ||v||^2   = (25, 25, 25, 25)
    v / ||v|| = (0.69282, 0.6, 0.4, 0)
    v • u   = (15.4641, 15.4641, 15.4641, 15.4641)
    v x u     = (5, -8.3923, 3.9282, 0)
    */
    cout << endl;
    cout << "||v||     = " << XMVector3Length(v) << endl;
    cout << "||v||^2   = " << XMVector3LengthSq(v) << endl; // the same as v•v
    cout << "v / ||v|| = " << XMVector3Normalize(v) << endl;
    cout << "v • u   = " << XMVector3Dot(v, u) << endl;
    cout << "v x u     = " << XMVector3Cross(v, u) << endl;
    cout << endl;

    // Test vectors.
    XMVECTOR n = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
    XMVECTOR w = XMVectorSet(0.8f, 0.7f, 0.0f, 0.0f);

    // Calculate components of a vector w projected on a normal vector n. 
    // Two component vectors are calculated:
    // projW - the orthogonal projection of w on the normal vector n
    // perpW - the orthogonal projection of w on the vector perpendicular to n
    // IMPORTANT: the vector n has to be normalized.
    /*
    projW = (0.8, 0, 0)
    perpW = (0, 0.7, 0)
    projW + perpW == w

    The angle between projW and perpW:
    [rad] = 1.5708
    [deg] = 90
    */
    XMVECTOR projW;
    XMVECTOR perpW;
    XMVector3ComponentsFromNormal(&projW, &perpW, w, n);
    cout << "projW = " << projW << endl;
    cout << "perpW = " << perpW << endl;

    // Check if projW + perpW == w
    // The projW and perpW are components of w.
    if (XMVector3Equal(projW + perpW, w))
        cout << "projW + perpW == w" << endl;
    else
        cout << "projW + perpW != w" << endl;
    cout << endl;

    // Calculate the angle between projW and perpW.
    // It should always be 90 degrees.
    XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);
    float angleRadians = XMVectorGetX(angleVec);
    float angleDegrees = XMConvertToDegrees(angleRadians);
    cout << "The angle between projW and perpW:" << endl;
    cout << "[rad] = " << angleRadians << endl;
    cout << "[deg] = " << angleDegrees << endl;

    // Test vector.
    v = XMVectorSet(8.0f, 13.0f, 2.67f, 0.0f);

    // Compute the vector ov orthogonal (i.e., perpendicular) to the vector v.
    // Note that the XMVector3Orthogonal function computes one of many possible 
    // perpendicular vectors. Also, note that the cross product is not normalized.
    /*
    ov = (15.67, -8, -8)
    ov • v = (0, 0, 0)
    ov x v = (82.64, -105.839, 267.71)               // not normalized
    norm(ov x v) = (0.275927, -0.353386, 0.893858)   // normalized
    */
    XMVECTOR ov = XMVector3Orthogonal(v);
    cout << endl;
    cout << "ov           = " << ov << endl;
    cout << "ov • v     = " << XMVector3Dot(ov, v) << endl; // always 0 as the vectors are orthogonal
    cout << "ov x v       = " << XMVector3Cross(ov, v) << endl;
    cout << "norm(ov x v) = " << XMVector3Normalize(XMVector3Cross(ov, v)) << endl;
    cout << endl;

    // Calculate a vector where each component is the product of the corresponding 
    // components of V1 and V2.
    XMVECTOR v1 = XMVectorSet(2.0f, 3.0f, 5.0f, 8.0f);
    XMVECTOR v2 = XMVectorSet(4.0f, 7.0f, 5.0f, 6.0f);
    cout << "v1 (x) v2 = " << XMVectorMultiply(v1, v2) << endl; // (8, 21, 25, 48)

    // Saturate each component of a vector to the range 0.0f to 1.0f.
    v = XMVectorSet(2.0f, -0.5f, 0.5f, 0.1f);
    cout << XMVectorSaturate(v) << endl; // (1, 0, 0.5, 0.1)
    v = XMVectorSet(2.3f, -1.5f, 0.7f, 1.1f);
    cout << XMVectorSaturate(v) << endl; // (1, 0, 0.7, 1)

    v1 = XMVectorSet(2.f, 7.f, 5.f, 8.f);
    v2 = XMVectorSet(4.f, 3.f, 9.f, 6.f);

    // Return a vector containing the smallest components between the two vectors.
    cout << XMVectorMin(v1, v2) << endl; // (2, 3, 5, 6)

    // Return a vector containing the largest components between the two vectors.
    cout << XMVectorMax(v1, v2) << endl; // (4, 7, 9, 8)

    cout << endl;
}

// used in VectorEquality
bool Equals(float lhs, float rhs)
{
    using std::numeric_limits;

    return (fabs(lhs - rhs) < numeric_limits<float>::epsilon());
}

void VectorEquality()
{
    using std::numeric_limits;

    cout.precision(8);

    XMVECTOR v = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
    XMVECTOR n = XMVector3Normalize(v);

    // Obtain the length of the normalized vector. It should be 1.0 but it's not.
    float len = XMVectorGetX(XMVector3Length(n));
    cout << "|n| == " << len << endl; // 0.99999994

    // Raising a float to a power, compounds the numeric error.
    cout << "|n|^88 == " << powf(len, 88.0f) << endl; // 0.99999475

    // Test that the absolute value of the difference is less than
    // a specified small value (the epsilon).
    if (Equals(len, 1.0f))
        cout << "|n| equals 1" << endl;
    else
        cout << "|n| not equals 1" << endl;

    // To test for equality we could also use the XMVector3NearEqual function.
    XMVECTOR vLen = XMVectorReplicate(len);
    XMVECTOR vComp = XMVectorReplicate(1.0f);
    XMVECTOR vEpsilon = XMVectorReplicate(numeric_limits<float>::epsilon());
    if (XMVector3NearEqual(vLen, vComp, vEpsilon))
        cout << "|n| equals 1" << endl;
    else
        cout << "|n| not equals 1" << endl;

    cout << endl;
}

void OtherTypes()
{
    using namespace DirectX::PackedVector;

    // Supported types:
    // HALF, SHORT, BYTE, INT

    // XMBYTE4 stores four 8-bit signed values.
    XMBYTE4 b = { 63.0f, 88.0f, -72.0f, -101.0f };
    cout << b << endl;

    XMVECTOR v = XMLoadByte4(&b);
    cout << v << endl;

    XMBYTE4 b1;
    XMStoreByte4(&b1, v); // b1 = v
    cout << b1 << endl;
}

// Converts XMVECTOR to XMFLOAT3
inline XMFLOAT3 VectorToFloat3(const FXMVECTOR& v)
{
    using namespace DirectX;

    XMFLOAT3 f;
    XMStoreFloat3(&f, v);
    return f;
}
