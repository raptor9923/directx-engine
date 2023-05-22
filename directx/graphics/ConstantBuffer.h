#pragma once
#include <d3d11.h>
#include "ConstantBuferTypes.h"
#include<wrl/client.h>
#include"../ErrorLogger.h"

template <class T>

class ConstantBuffer
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	ID3D11DeviceContext* m_deviceContextPtr;
	T m_data;
	ConstantBuffer(const ConstantBuffer<T>& rhs);
public:

	ConstantBuffer() = default;

	T* AccessDataMembers()
	{
		return &m_data;
	}
	ID3D11Buffer* Get() const
	{
		return m_buffer.Get();
	}
	ID3D11Buffer* const* GetAddressOf()
	{
		return m_buffer.GetAddressOf();
	}
	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		if (m_buffer.Get() != nullptr)
			m_buffer.Reset();
		m_deviceContextPtr = deviceContext;
		D3D11_BUFFER_DESC constantBufferDesc;
		ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));
		constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;   // dynamic usage allows changing of the resource
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // specifies buffer as constant buffer
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // allows CPU to write to the resource
		constantBufferDesc.MiscFlags = 0;   // additional options for buffer
		constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));   // constant buffers must be 16 byte or multiple of this
		constantBufferDesc.StructureByteStride = 0;

		HRESULT hr = device->CreateBuffer(&constantBufferDesc, nullptr, m_buffer.GetAddressOf());
		return hr;
	}

	bool ApplyChanges()
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		ZeroMemory(&mappedSubResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr = m_deviceContextPtr->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);   // get a pointer to resource and block GPU from accessing it
		if (FAILED(hr))
		{
			ErrorLogger::errorLog(hr, "Failed to map constant buffer");
			return false;
		}
		CopyMemory(mappedSubResource.pData, &m_data, sizeof(T));   // copy data to resource
		m_deviceContextPtr->Unmap(m_buffer.Get(), 0);   // unlock resource for GPU
		return true;
	}
};