#pragma once

/*
Matrices are supported through the XMMATRIX type - an array of four XMVECTOR objects. 
Just as with XMVECTOR, XMMATRIX objects aren't good candidates for class storage. 
Types such as XMFLOAT3X3 and XMFLOAT4X4 should be used instead. 

XMFLOAT4X4 has the following structure:

struct XMFLOAT4X4
{
    union
    {
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };
}

Thus, you can access elements in traditional matrix subscript form or through 
zero-based [row, column] array access.

CallingConventions
------------------
- Use FXMMATRIX for the first argument
- Use CXMMATRIX for everything else
A few exceptions to this rule apply.

Examples:
void XMStoreFloat4x4(_Out_ XMFLOAT4X4* pDestination, _In_ FXMMATRIX M);
XMMATRIX XMMatrixMultiply(FXMMATRIX M1, CXMMATRIX M2);
XMMATRIX XMMatrixMultiplyTranspose(FXMMATRIX M1, CXMMATRIX M2);

*/

void MatrixInitialization();
void MatrixFunctions();
void MatrixTransforms();
void MatrixOperators();
void MatrixLoadingStoring();