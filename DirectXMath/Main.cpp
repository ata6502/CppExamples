#include <windows.h> // for XMVerifyCPUSupport
#include <iostream>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#include "Vectors.h"
#include "Matrices.h"
#include "Colors.h"
#include "Operations.h"
#include "Planes.h"

int main()
{
    // XMVerifyCPUSupport is the only function that requires <windows.h>
    if (!DirectX::XMVerifyCPUSupport())
    {
        std::cout << "SSE2 not supported" << std::endl;
        return 0;
    }

    // 1 - vectors
    // 2 - matrices
    // 3 - colors
    // 4 - operations
    // 5 - planes
    int test = 5;

    switch (test)
    {
    case 1:
        // vectors
        VectorSetters();
        VectorLoading();
        VectorStoring();
        ConstVectors();
        VectorOperators();
        VectorFunctions();
        VectorEquality();
        OtherTypes();
        break;

    case 2:
        // matrices
        MatrixInitialization();
        MatrixFunctions();
        MatrixTransforms();
        MatrixOperators();
        MatrixLoadingStoring();
        break;

    case 3:
        // colors
        ColorConversion();
        ColorFunctions();
        break;

    case 4:
        // operations
        ArithmeticOperations();
        Swizzling();
        AngleConversion();
        Constants();
        MinMax();
        break;

    case 5:
        PointPlaneSpatialRelation();
        PlaneConstruction();
        PlaneNormalization();
        PlaneTransformation();
        PlaneLineIntersection();
        ReflectionPlane();
        break;
    }

    return 0;
}



