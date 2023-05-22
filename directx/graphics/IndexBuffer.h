#pragma once
#include <d3d11.h>
#include<wrl/client.h>
#include<vector>

class IndexBuffer
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	UINT m_bufferSize = 0;
	IndexBuffer(const IndexBuffer& indexBuffer);
public:
	IndexBuffer() = default;
	ID3D11Buffer* Get() const
	{
		return m_buffer.Get();
	}
	ID3D11Buffer* const* GetAddressOf()
	{
		return m_buffer.GetAddressOf();
	}
	UINT BufferSize() const
	{
		return m_bufferSize;
	}
	HRESULT Initialize(ID3D11Device* device,const DWORD* data, UINT numIndices)
	{
		if (m_buffer.Get() != nullptr)
			m_buffer.Reset();
		m_bufferSize = numIndices;
		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;   // default type of buffer
		indexBufferDesc.ByteWidth = sizeof(DWORD) * numIndices;   // size of buffer
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;   // specify buffer as index buffer 
		indexBufferDesc.CPUAccessFlags = 0;   // CPU can't access
		indexBufferDesc.MiscFlags = 0;   // additional options for buffer

		D3D11_SUBRESOURCE_DATA indexBufferData;
		ZeroMemory(&indexBufferData, sizeof(indexBufferData));
		indexBufferData.pSysMem = data;
		HRESULT hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_buffer.GetAddressOf());
		if (FAILED(hr))
		{
			ErrorLogger::errorLog(hr, "Failed to create index Buffer");
			return hr;
		}
		return hr;
	}
};