#pragma once

/*
When representing a plane in code, it suffices to store only the normal vector n and the constant d. 
It is useful to think of this as a 4D vector (n, d) = (a, b, c, d). Therefore, because the XMVECTOR 
type stores a 4-tuple of floating-point values, the DirectXMath library overloads the XMVECTOR type 
to also represent planes.

The DirectXMath functions use an XMVECTOR 4-vector to represent the coefficients of the plane equation, 
Ax+By+Cz+D = 0, where the X-component is A, the Y-component is B, the Z-component is C, and the W-component is D.
*/

void PointPlaneSpatialRelation();
void PlaneConstruction();
void PlaneNormalization();
void PlaneTransformation();
void PlaneLineIntersection();
void ReflectionPlane();
