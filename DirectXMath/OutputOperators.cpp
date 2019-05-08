#include "OutputOperators.h"

using namespace DirectX;
using std::ostream;

// Overload the << operator to output XMVECTOR.
ostream& operator<<(ostream& os, FXMVECTOR v)
{
    XMFLOAT4 vd;
    XMStoreFloat4(&vd, v); // store XMVECTOR in XMFLOAT4
    os << "(" << vd.x << ", " << vd.y << ", " << vd.z << ", " << vd.w << ")";
    return os;
}

// Overload the << operator to output XMFLOAT2.
ostream& operator<<(ostream& os, XMFLOAT2 v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

// Overload the << operator to output XMFLOAT3.
ostream& operator<<(ostream& os, XMFLOAT3 v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

// Overload the << operator to output XMFLOAT4.
ostream& operator<<(ostream& os, XMFLOAT4 v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}

// Overload the << operator to output XMBYTE4.
ostream& operator<<(ostream& os, DirectX::PackedVector::XMBYTE4 b)
{
    os << "(" << b.x << ", " << b.y << ", " << b.z << ", " << b.w << ")";
    return os;
}

// Overload the << operator to output XMMATRIX.
ostream& operator<<(ostream& os, CXMMATRIX m)
{
    XMFLOAT4X4 md;
    XMStoreFloat4x4(&md, m); // load XMMATRIX into XMFLOAT4x4
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
            os << md(i, j) << "\t";
        os << std::endl;
    }
    return os;
}

// Overload the << operator to output XMFLOAT4X4.
ostream& operator<<(ostream& os, XMFLOAT4X4 m)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
            os << m(i, j) << "\t";
        os << std::endl;
    }
    return os;
}
