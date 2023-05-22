#pragma once
#include<DirectXMath.h>


// normal matrix
struct  CB_VS_vertexshader
{
	DirectX::XMMATRIX mat;
};

struct CB_PS_pixelshader
{
	float alpha=1.0f;
};