#include <iostream>
#include <DirectXPackedVector.h> // for XMCOLOR

#include "OutputOperators.h"
#include "Colors.h"

using namespace DirectX;

using std::cout;
using std::endl;

void ColorConversion()
{
    using namespace DirectX::PackedVector;

    XMVECTOR v;

    // Convert XMCOLOR to XMVECTOR.

    const XMCOLOR c1 = { .5f, .25f, .3f, .1f };
    v = XMLoadColor(&c1);
    cout << "v = " << v << endl; // v = (0.501961, 0.25098, 0.298039, 0.101961)

    XMCOLOR c2 = XMCOLOR(.2f, .3f, .1f, .5f);
    v = XMLoadColor(&c2);
    cout << "v = " << v << endl; // v = (0.2, 0.298039, 0.101961, 0.501961)
                                 
    XMCOLOR c3;
    c3.r = 128;
    c3.g = 64;
    c3.b = 255;
    c3.a = 128;
    v = XMLoadColor(&c3);
    cout << "v = " << v << endl; // v = (0.501961, 0.25098, 0, 0.501961)

    // Convert XMVECTOR to XMCOLOR.

    v = XMVectorSet(0.5f, 0.25f, 0, 1.0f);
    XMCOLOR color;
    XMStoreColor(&color, v);
    cout << "color (dec) = " << std::dec << color << endl; // color (dec) = 4286595072
    cout << "color (hex) = " << std::hex << color << endl; // color (hex) = ff804000
}

void ColorFunctions()
{
    // Calculate (c1.r, c1.g, c1.b, c1.a) (x) (c2.r, c2.g, c2.b, c2.a)
    const XMVECTORF32 c1 = { 1.f, 3.f, 2.f, 4.f };
    const XMVECTORF32 c2 = { 7.f, 3.f, 3.f, 2.f };

    XMVECTOR c = XMColorModulate(c1, c2);
    cout << "c = " << c << endl;

}
