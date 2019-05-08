#pragma once

#include <iostream>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

std::ostream& operator<<(std::ostream& os, DirectX::FXMVECTOR v);
std::ostream& operator<<(std::ostream& os, DirectX::XMFLOAT2 v);
std::ostream& operator<<(std::ostream& os, DirectX::XMFLOAT3 v);
std::ostream& operator<<(std::ostream& os, DirectX::XMFLOAT4 v);
std::ostream& operator<<(std::ostream& os, DirectX::PackedVector::XMBYTE4 b);
std::ostream& operator<<(std::ostream& os, DirectX::CXMMATRIX m);
std::ostream& operator<<(std::ostream& os, DirectX::XMFLOAT4X4 m);
