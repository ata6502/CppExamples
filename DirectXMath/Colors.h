#pragma once

/*
128-bit Color
- can be represented mathematically by a 4D vector (r, g, b, a) and in DirectXMath by the XMVECTOR type
- each component is a floating-point value from 0.0 to 1.0
- the componentwise multiplication is provided by the DirectXMath function XMColorModulate
- used where multiple color operations are performed (e.g., in a pixel shader); this minimizes arithmetic errors

32-bit Color
- can be represented by four bytes - one byte for each color component r, g, b, a
- in DirectXMath, 32-bit color can be represented by the XMCOLOR type (defined in DirectXPackedVector.h) which uses the ARGB layout
- used to store pixel colors in the back buffer

The XMCOLOR type stores alpha component in the most significant bits and the blue component in the least significant bits (A8R8G8B8):
XMCOLOR: [32] aaaaaaaa rrrrrrrr gggggggg bbbbbbbb [0]

Note that the 8-bit color components need to be packed into a uint32 value as ABGR, rather than ARGB because of endianness:
uint32:  [32] aaaaaaaa bbbbbbbb gggggggg rrrrrrrr [0]
*/

void ColorConversion();
void ColorFunctions();
