#include "Shaders.h"

bool VertexShader::Initialize(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::wstring& shaderPath,const D3D11_INPUT_ELEMENT_DESC* layoutDescription, UINT numElements)
{
	// load shader to blob
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), m_shaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::errorLog(hr, L"Failed to load shader to Blob");
		return false;
	}
	// create shader stored in blob
	hr = device->CreateVertexShader(m_shaderBuffer->GetBufferPointer(), m_shaderBuffer->GetBufferSize(), nullptr, m_shader.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::errorLog(hr, L"Failed to load vertex shader: " + shaderPath);
		return false;
	}
	// create input layout
	hr = device->CreateInputLayout(layoutDescription, numElements, m_shaderBuffer->GetBufferPointer(), m_shaderBuffer->GetBufferSize(), m_inputLayout.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::errorLog(hr, "Failed to create input layout.");
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader()
{
	return m_shader.Get();
}

ID3D10Blob* VertexShader::GetBuffer()
{
	return m_shaderBuffer.Get();
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return m_inputLayout.Get();
}


bool PixelShader::Initialize(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::wstring& shaderPath)
{
	// load shader to blob
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), m_shaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::errorLog(hr, L"Failed to load shader to Blob");
		return false;
	}
	// create shader stored in blob
	hr = device->CreatePixelShader(m_shaderBuffer->GetBufferPointer(), m_shaderBuffer->GetBufferSize(), NULL, m_shader.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::errorLog(hr, L"Failed to load pixel shader: " + shaderPath);
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return m_shader.Get();
}

ID3D10Blob* PixelShader::GetBuffer()
{
	return m_shaderBuffer.Get();
}