#include <iostream>

#include "OutputOperators.h"
#include "Matrices.h"

using namespace DirectX;

using std::cout;
using std::endl;

void MatrixInitialization()
{
    // Initialize an XMMATRIX using a ctor that accepts 16 individual floats.
    XMMATRIX A(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        2.0f, 4.0f, 3.0f, 1.0f);

    // Initialize an XMMATRIX using a ctor that accepts 4 XMVECTOR objects.
    XMMATRIX B(
        XMVectorSet(2.0f, 5.0f, 3.0f, 0.0f),
        XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),
        XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f),
        XMVectorSet(2.0f, 0.0f, 2.0f, 1.0f));

    // Create an instance of XMMATRIX using the XMMatrixSet function.
    XMMATRIX C = XMMatrixSet(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);

    // Initialize the identity matrix I.
    XMMATRIX I = XMMatrixIdentity();

    cout << "Matrix A\n" << A << endl << endl;
    cout << "Matrix B\n" << B << endl << endl;
    cout << "Matrix C\n" << C << endl << endl;
    cout << "Matrix I\n" << I << endl << endl;

    // Return true if M is the identity matrix: bool XMMatrixIsIdentity(FXMMATRIX M)
    cout.setf(std::ios_base::boolalpha);
    cout << "Matrix A is identity: " << XMMatrixIsIdentity(A) << endl;
    cout << "Matrix I is identity: " << XMMatrixIsIdentity(I) << endl;
    cout << endl;

    // XMMATRIX has an accessible member r for the array of XMVECTOR objects it contains.
    // You can use it in conjunction with the XMVECTOR accessor, mutator, and initialization functions.
    A.r[0] = XMVectorSetX(A.r[0], 11.0f);
    A.r[1] = XMVectorSetY(A.r[1], 22.0f);
    A.r[2] = XMVectorSetZ(A.r[2], 33.0f);
    A.r[3] = XMVectorSet(1.f, 2.f, 3.f, 4.f);

    cout << "Modified matrix A\n" << A << endl << endl;
}

void MatrixFunctions()
{
    XMMATRIX A(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        2.0f, 4.0f, 3.0f, 1.0f);

    XMMATRIX B(
        2.0f, 5.0f, 3.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 2.0f, 3.0f, 0.0f,
        2.0f, 0.0f, 2.0f, 1.0f);

    cout.precision(4);

    // Return the matrix product AB: XMMATRIX XMMatrixMultiply(FXMMATRIX A, CXMMATRIX B)
    cout << "A * B\n\n" << A * B << endl << endl;
    cout << "XMMatrixMultiply(A, B)\n" << XMMatrixMultiply(A, B) << endl << endl;

    // Return the matrix transpose: XMMATRIX XMMatrixTranspose(FXMMATRIX M)
    cout << "transpose(A)\n" << XMMatrixTranspose(A) << endl << endl;

    // Return the determinant of M as a vector (det M, det M, det M, det M): 
    // XMVECTOR XMMatrixDeterminant(FXMMATRIX M)
    cout << "det(A) = " << XMMatrixDeterminant(A) << endl << endl;

    // Return the inverse of M: XMMATRIX XMMatrixInverse(_Out_opt_ XMVECTOR* pDeterminant, _In_ FXMMATRIX M)
    XMVECTOR detA = XMMatrixDeterminant(A);
    XMMATRIX invA = XMMatrixInverse(&detA, A);
    cout << "inverse(A)\n" << invA << endl << endl;

    // Check the inverse matrix: A * invA should be the identity matrix.
    XMMATRIX C = A * invA;
    cout << "Matrix A * inverse(A) is identity: " << XMMatrixIsIdentity(C) << endl;

    cout << endl;
}

void MatrixTransforms()
{
    // Construct a scaling matrix.
    // scaleX, scaleY, scaleZ - scaling factors 
    //XMMATRIX XMMatrixScaling(float scaleX, float scaleY, float scaleZ);
    XMMATRIX S1 = XMMatrixScaling(1.f, 1.f, 1.5f);
    cout << "Scaling matrix S1\n" << S1 << endl << endl;

    // Construct a scaling matrix from components of a vector.
    //XMMATRIX XMMatrixScalingFromVector(FXMVECTOR scale);
    XMVECTOR scale = XMVectorSet(1.f, 1.f, 2.f, 1.0f);
    XMMATRIX S2 = XMMatrixScalingFromVector(scale);
    cout << "Scaling matrix S2\n" << S2 << endl << endl;

    // Construct axes of rotation: Rx, Ry, and Rz
    // 'angle' - a rotation angle specified clockwise
    //XMMATRIX XMMatrixRotationX(float angle);
    //XMMATRIX XMMatrixRotationY(float angle);
    //XMMATRIX XMMatrixRotationZ(float angle);
    XMMATRIX RX = XMMatrixRotationX(XM_PIDIV4); // PI/4 == 45deg
    cout << "Rotation matrix 45 deg around X axis:\n" << RX << endl << endl;

    XMMATRIX RY = XMMatrixRotationY(XM_PIDIV4);
    cout << "Rotation matrix 45 deg around Y axis:\n" << RY << endl << endl;

    XMMATRIX RZ = XMMatrixRotationZ(XM_PIDIV4);
    cout << "Rotation matrix 45 deg around Z axis:\n" << RZ << endl << endl;

    // Construct a rotation matrix around an arbitrary axis.
    // 'axis' - an axis to rotate about
    // 'angle' - a rotation angle specified clockwise
    //XMMATRIX XMMatrixRotationAxis(FXMVECTOR axis, float angle);
    XMVECTOR rotAxis = XMVectorSet(1.f, 2.f, 1.f, 0.f);
    XMMATRIX R = XMMatrixRotationAxis(rotAxis, XM_PIDIV4);
    cout << "Rotation axis: " << rotAxis << endl;
    cout << "Rotation matrix 45 deg around the rotation axis:\n" << R << endl << endl;

    // Construct a translation matrix.
    //XMMATRIX XMMatrixTranslation(float offsetX, float offsetY, float offsetZ);
    XMMATRIX T1 = XMMatrixTranslation(1.f, 2.f, 3.f);
    cout << "Translation matrix T1\n" << T1 << endl << endl;

    // Construct a translation matrix from components of a vector.
    //XMMATRIX XMMatrixTranslationFromVector(FXMVECTOR offset);
    XMVECTOR trans = XMVectorSet(10.f, 20.f, 30.f, 0.f);
    XMMATRIX T2 = XMMatrixTranslationFromVector(trans);
    cout << "Translation matrix T2\n" << T2 << endl << endl;

    // Transform the vector v by matrix M. In other words: compute the vector-matrix product vM. 
    // XMVector3Transform ignores the w component of the input vector, and uses a value of 1.0 instead.
    // The w component of the returned vector may be non-homogeneous (not 1.0).
    //XMVECTOR XMVector3Transform(FXMVECTOR v, FXMMATRIX M);
    XMVECTOR vecIn = XMVectorSet(1.f, 2.f, 3.f, 1.f);
    XMMATRIX M = XMMatrixSet(
        2.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 3.f, 0.f,
        2.f, 4.f, 3.f, 1.f);
    XMVECTOR vecOut1 = XMVector3Transform(vecIn, M);
    cout << "vecOut = " << vecOut1 << endl << endl;

    // Transform the vector v by matrix M, where v.w = 1 (for transforming points).
    // XMVector3TransformCoord ignores the w component of the input vector, and uses a value of 1.0 instead.
    // The w component of the returned vector is guaranteed to be 1.0
    //XMVECTOR XMVector3TransformCoord(FXMVECTOR v, FXMMATRIX M);
    XMVECTOR vecOut2 = XMVector3TransformCoord(vecIn, M);
    cout << "vecOut = " << vecOut2 << endl << endl;

    // Transform the vector v by matrix M, where v.w = 0 (for transforming vectors).
    // The 4th row (the translation row) is ignored.
    //XMVECTOR XMVector3TransformNormal(FXMVECTOR v, FXMMATRIX M);
    XMVECTOR vecOut3 = XMVector3TransformNormal(vecIn, M);
    cout << "vecOut = " << vecOut3 << endl << endl;
}

void MatrixOperators()
{
    // Matrix-to-matrix addition, subtraction, and multiplication.

    XMMATRIX A = XMMatrixSet(
        1.f, 0.f, 0.f, 6.f,
        0.f, 0.f, 0.f, 1.f,
        1.f, 0.f, 2.f, 0.f,
        0.f, 4.f, 0.f, 0.f);

    XMMATRIX B = XMMatrixSet(
        0.f, 0.f, 0.f, 0.f,
        2.f, 0.f, 7.f, 2.f,
        2.f, 0.f, 3.f, 0.f,
        0.f, 4.f, 0.f, 0.f);

    cout << "A + B" << endl << A + B << endl << endl;
    cout << "A - B" << endl << A - B << endl << endl;
    cout << "A * B" << endl << A * B << endl << endl;
    cout << "-A" << endl << -A << endl << endl;

    XMMATRIX C = XMMatrixIdentity();

    // XMMATRIX& operator+= (FXMMATRIX M);
    C += A;
    cout << "C" << endl << C << endl << endl;

    // XMMATRIX& operator-= (FXMMATRIX M);
    C -= A;
    cout << "C" << endl << C << endl << endl;

    // XMMATRIX& operator*= (FXMMATRIX M);
    C *= B;
    cout << "C" << endl << C << endl << endl;

    // Scalar-to-matrix multiplication and division.

    // XMMATRIX operator* (float S) const; 
    cout << "2 * A" << endl << 2.0f * A << endl << endl;

    // XMMATRIX operator/ (float S) const;
    cout << "A / 2" << endl << A / 2.0f << endl << endl;

    // XMMATRIX& operator*= (float S);
    C = A;
    C *= 3.0f;
    cout << "C" << endl << C << endl << endl;

    // XMMATRIX& operator/= (float S);
    C /= 3.0f;
    cout << "C" << endl << C << endl << endl;
}

void MatrixLoadingStoring()
{
    XMFLOAT4X4 A(
        1.f, 0.f, 0.f, 6.f,
        0.f, 0.f, 0.f, 1.f,
        1.f, 0.f, 2.f, 0.f,
        0.f, 4.f, 0.f, 0.f);

    // Load XMFLOAT4X4 into XMMATRIX.
    XMMATRIX M = XMLoadFloat4x4(&A);
    cout << "M" << endl << M << endl << endl;

    // Store XMMATRIX in XMFLOAT4X4.
    XMFLOAT4X4 B;
    XMStoreFloat4x4(&B, M);
    cout << "B" << endl << B << endl << endl;
}
