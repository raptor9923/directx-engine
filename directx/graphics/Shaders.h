#pragma once
#include "../ErrorLogger.h"
#include <d3d11.h>
#include<wrl/client.h>
#include<d3dcompiler.h>
#pragma comment(lib,"D3DCompiler.lib")
class VertexShader
{
	Microsoft::WRL::ComPtr <ID3D11VertexShader> m_shader{ nullptr };
	Microsoft::WRL::ComPtr <ID3DBlob> m_shaderBuffer{ nullptr };
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
public:
	bool Initialize(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::wstring& shaderPath, const D3D11_INPUT_ELEMENT_DESC* layoutDescription, UINT numElements);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();
	ID3D11InputLayout* GetInputLayout();
};

class PixelShader
{
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shader{ nullptr };
	Microsoft::WRL::ComPtr <ID3DBlob> m_shaderBuffer{ nullptr };
public:
	bool Initialize(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::wstring& shaderPath);
	ID3D11PixelShader* GetShader();
	ID3D10Blob* GetBuffer();
};