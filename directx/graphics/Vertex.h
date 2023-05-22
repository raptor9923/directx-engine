#pragma once
#include<DirectXMath.h>

struct Vertex
{
	DirectX::XMFLOAT3 m_pos{};
	DirectX::XMFLOAT2 m_texCoord{};
	Vertex() = default;
	Vertex(float x, float y, float z, float u, float v)
		: m_pos(x, y, z), m_texCoord(u, v) {}
};