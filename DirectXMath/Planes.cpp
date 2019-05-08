#include <iostream>

#include "OutputOperators.h"
#include "Planes.h"

using namespace DirectX;

using std::cout;
using std::endl;

void PointPlaneSpatialRelation()
{
    cout << "Test the locality of a point relative to a plane." << endl;

    // XMPlaneDotCoord(P,V) calculates the dot product between a plane P and a 3D vector V.
    // V.w is always treated as 1.0f which means that V describes a 3D point.

    // The plane P is an XMVECTOR describing the plane coefficients (A, B, C, D) 
    // for the plane equation Ax+By+Cz+D=0.

    // XMPlaneDotCoord is useful for determining spatial relation of a point and a plane:
    // - if XMPlaneDotCoord(P,V) > 0 then V is in front of the plane
    // - if XMPlaneDotCoord(P,V) < 0 then V is behind the plane
    // - if XMPlaneDotCoord(P,V) = 0 then V is on the plane

    float x;
    XMVECTOR v;

    XMVECTOR p = XMVectorSet(0.f, 1.f, 0.f, 0.f); // plane

    v = XMVectorSet(3.f, 5.f, 2.f, 1.f); // point "above" the plane
    x = XMVectorGetX(XMPlaneDotCoord(p, v));
    if (abs(x) < FLT_EPSILON) cout << "v1 is coplanar to the plane." << endl;
    if (x > 0) cout << "v1 is in positive half-space." << endl;
    if (x < 0) cout << "v1 is in negative half-space." << endl;

    v = XMVectorSet(3.f, -5.f, 2.f, 1.f); // point "below" the plane
    x = XMVectorGetX(XMPlaneDotCoord(p, v));
    if (abs(x) < FLT_EPSILON) cout << "v2 is coplanar to the plane." << endl;
    if (x > 0) cout << "v2 is in positive half-space." << endl;
    if (x < 0) cout << "v2 is in negative half-space." << endl;

    v = XMVectorSet(0.f, 0.f, 0.f, 1.f); // point lies "on" the plane
    x = XMVectorGetX(XMPlaneDotCoord(p, v));
    if (abs(x) < FLT_EPSILON) cout << "v3 is coplanar to the plane." << endl;
    if (x > 0) cout << "v3 is in positive half-space." << endl;
    if (x < 0) cout << "v3 is in negative half-space." << endl;


    // XMPlaneDotNormal(P,V) calculates the dot product between the normal vector of a plane and a 3D vector.
    // V.w is always treated as 0.0f which means that V describes a 3D vector.

    // The plane P is an XMVECTOR describing the plane coefficients (A, B, C, D) 
    // for the plane equation Ax+By+Cz+D=0.

    // XMPlaneDotNormal is useful for calculating the angle between the normal vector 
    // of the plane, and another normal vector.

    v = XMVectorSet(0.f, 0.f, 1.f, 0.f);
    v = XMVectorSet(cos(XM_PIDIV4), sin(XM_PIDIV4), 0.f, 0.f);
    x = XMVectorGetX(XMPlaneDotNormal(p, v)); // returns p•v = cos(p,v)
    cout << "Angle: " << XMConvertToDegrees(acos(x)) << endl;
}

void PlaneConstruction()
{
    XMVECTOR plane, point, normal;

    // Construct a plane by directly specifying plane coefficients.
    plane = XMVectorSet(0.5f, 1.f, 0.5f, 0.3f); // 0.5x+y+0.5z+0.3=0
    cout << "Plane1: " << plane << endl;

    // Construct a plane from a normal and a known point on the plane.
    normal = XMVectorSet(0.f, 1.f, 0.f, 0.f); // n
    point = XMVectorSet(1.f, 0.f, 0.f, 0.f); // p0
    plane = XMPlaneFromPointNormal(point, normal); // 0x+y+0z+0=0, where d = -n•p0
    cout << "Plane2: " << plane << endl;

    // Construct a plane given three points on the plane.
    // Given the points p0, p1, p2, we can form two vectors on the plane: u = p1 - p0 and v = p2 - p0
    // From that we can compute the normal of the plane by taking the cross product of the two vectors 
    // on the plane : n = u x v (remember the left-hand thumb rule.) Then, we compute d = -n•p0.

    XMVECTOR p0 = XMVectorSet(0, 1, 0, 1);
    XMVECTOR p1 = XMVectorSet(-1, 3, 6, 1);
    XMVECTOR p2 = XMVectorSet(8, 5, 3, 1);

    plane = XMPlaneFromPoints(p0, p1, p2);
    cout << "Plane3: " << plane << endl;

    // Obtain the plane's coefficients (which are also the coordinates of the plane normal and d???).
    float nx = XMVectorGetX(plane);
    float ny = XMVectorGetY(plane);
    float nz = XMVectorGetZ(plane);
    float d = XMVectorGetW(plane);

    // Construct a plane given three points on the plane without using XMPlaneFromPoints.
    XMVECTOR u = XMVectorSubtract(p1, p0); // p1-p0
    XMVECTOR v = XMVectorSubtract(p2, p0); // p2-p0
    XMVECTOR n = XMVector3Normalize(XMVector3Cross(u, v));

    nx = XMVectorGetX(n);
    ny = XMVectorGetY(n);
    nz = XMVectorGetZ(n);
    d = XMVectorGetX(XMVector3Dot(-n, p0));

    plane = XMVectorSet(nx, ny, nz, d);
    cout << "Plane3: " << plane << endl;
}

void PlaneNormalization()
{
    XMVECTOR plane = XMVectorSet(0.5f, 1.f, 0.5f, 0.3f); // 0.5x+y+0.5z+0.3=0

    // Normalize a plane's normal vector.
    XMVECTOR normalizedPlane = XMPlaneNormalize(plane);

    cout << "Normalized plane: " << normalizedPlane << endl;
}

void PlaneTransformation()
{
    // Transform a plane (n, d) by treating it as a 4D vector and multiplying it by the inverse-transpose 
    // of the desired transformation matrix. Note that the plane's normal vector must be normalized first.

    XMVECTOR plane = XMVectorSet(0.5f, 1.f, 0.5f, 0.3f); // 0.5x+y+0.5z+0.3=0
    plane = XMPlaneNormalize(plane); // make sure the plane normal is normalized

    // Initialize T to a desired transformation.
    XMMATRIX T(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        2.0f, 4.0f, 3.0f, 1.0f);

    // Transform a plane P by a matrix T.
    // XMVECTOR XMPlaneTransform(FXMVECTOR P, FXMMATRIX T)

    XMVECTOR detT = XMMatrixDeterminant(T);
    XMMATRIX invT = XMMatrixInverse(&detT, T);
    XMMATRIX invTransposeT = XMMatrixTranspose(invT);
    XMVECTOR transformedPlane = XMPlaneTransform(plane, invTransposeT);

    cout << "Transformed plane: " << transformedPlane << endl;
}

void PlaneLineIntersection()
{
    // Find the intersection between a plane and a line.
    // XMVECTOR XMPlaneIntersectLine(FXMVECTOR Plane, FXMVECTOR LinePoint1, FXMVECTOR LinePoint2)

    XMVECTOR plane = XMVectorSet(1.f / sqrt(3.f), 1.f / sqrt(3.f), 1.f / sqrt(3.f), -5.f);
    XMVECTOR p1 = XMVectorSet(-1, 1, -1, 0);
    XMVECTOR p2 = XMVectorSet(0, 1, -1, 0);

    XMVECTOR s = XMPlaneIntersectLine(plane, p1, p2);

    cout << "Intersection: " << s << endl;
}

void ReflectionPlane()
{
    XMVECTOR n, d, p, r;

    // Construct a plain.
    XMVECTOR plane = XMVectorSet(-1.f / sqrt(2.f), 1.f / sqrt(2.f), 0.f, 5.f / sqrt(2.f));
    plane = XMPlaneNormalize(plane); //  make sure the plane is normalized

    // Construct a point.
    p = XMVectorSet(0, 1, 0, 1);

    // Construct the reflection matrix given a plane.
    // XMMATRIX XMMatrixReflect(FXMVECTOR ReflectionPlane)
    XMMATRIX M = XMMatrixReflect(plane);

    // Multiply p by M to obtain the reflected point r.
    r = XMVector3Transform(p, M); // transforms p as a point, not as a vector

    cout << "Reflected point (method #1): " << r << endl;

    // The above code is an equivalent to evaluating the formula r = p – 2(n•p + d)n

    // plane(n, d)
    n = XMVectorSet(-1.f / sqrt(2.f), 1.f / sqrt(2.f), 0.f, 0.f); // normalized
    d = XMVectorReplicate(5.f / sqrt(2.f));

    // point
    p = XMVectorSet(0, 1, 0, 1);

    // Reflect the point p.
    r = XMVectorSubtract(p, 2.0f*((XMVector3Dot(n, p) + d) * n));

    cout << "Reflected point (method #2): " << r << endl;

    // The same can be accomplished using the formula r = p – 2projn(p – p0)
    n = XMVectorSet(-1.f / sqrt(2.f), 1.f / sqrt(2.f), 0.f, 0.f); // normalized
    p = XMVectorSet(0, 1, 0, 1);
    XMVECTOR p0 = -(5.f / sqrt(2.f)) * n; // calculated from d = -n•p0   =>   p0 = -(1/d)nT  (nT is the transpose of n)
                                          // ??? it seems 1/d = sqrt(2.f)/5.f, not 5.f/sqrt(2.f) but the result is anyway correct

    XMVECTOR proj_n, perp_n;
    XMVector3ComponentsFromNormal(&proj_n, &perp_n, XMVectorSubtract(p, p0), n);
    r = XMVectorSubtract(p, 2.0f*proj_n);

    cout << "Reflected point (method #3): " << r << endl;
}