#pragma once

#include <DirectXMath.h>

/*
The core vector type in DirectXMath is a 128-bit XMVECTOR which can process four 32-bit floating point 
components with a single SIMD instruction. It is aligned on a 16 byte boundary.

- When doing calculations, vectors must be of type XMVECTOR to take advantage of SIMD.
- The XMFLOAT2, XMFLOAT3, and XMFLOAT4 data members have to be converted to XMVECTOR in order to take advantage of SIMD. The results can be converted back from XMVECTOR to XMFLOAT2, XMFLOAT3, and XMFLOAT4 using storage functions.
- XMVECTOR variables have to be 16-byte aligned. Local and global XMVECTOR variables are 16-byte aligned automatically.
- For class data members, use XMFLOAT2, XMFLOAT3, and XMFLOAT4 types.
- In XMVECTOR individual vector components are inaccessible as structure members. On the other hand, the types XMFLOAT2, XMFLOAT3, and XMFLOAT4 have accessible members (x, y, z, and w).
- If you want to access an individual component of XMVECTOR, use an accessor (such as XMVector3GetX) or a mutator (such as XMVector3SetX).
- Use XMVECTORF32 or XMVECTORU32 for constant vectors that require initialization syntax.
- It can be done with the loading functions. 
- The XMVECTOR has several overloaded operators for doing vector addition, subtraction, and scalar multiplication.
- Operator overloading can be disabled by defining XM_NO_OPERATOR_OVERLOADS. The reason some application would want to disable operator overloading is for performance, as the function versions can be faster when forming complex expressions.

Vector equality:
- Do not compare floats for equality or inequality. Rather, test that the absolute value of the difference is less that a specified small value: | a – b | < e

CallingConventions
------------------
- Use FXMVECTOR for the first three XMVECTOR input parameters.
- Use GXMVECTOR for the fourth XMVECTOR input parameter.
- Use HXMVECTOR for the fifth and sixth XMVECTOR input parameters.
- Use CXMVECTOR for any additional XMVECTOR input parameters.
- Use XMVECTOR* or XMVECTOR& for all output parameters.
*/

void VectorSetters();
void VectorLoading();
void VectorStoring();
void ConstVectors();
void VectorOperators();
void VectorFunctions();
void VectorEquality();
void OtherTypes();

inline DirectX::XMFLOAT3 VectorToFloat3(const DirectX::FXMVECTOR& v);

