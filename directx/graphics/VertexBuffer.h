#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include <memory>

template <class T>
class VertexBuffer
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	std::unique_ptr<UINT> m_stride;
	UINT m_bufferSize{};
	VertexBuffer(const VertexBuffer<T>& rhs);
public:
	VertexBuffer() = default;

	ID3D11Buffer* Get() const
	{
		return m_buffer.Get();
	}
	ID3D11Buffer* const* GetAddressOf() const
	{
		return m_buffer.GetAddressOf();
	}
	UINT BufferSize()
	{
		return m_bufferSize;
	}
	UINT Stride() const
	{
		return *m_stride.get();
	}
	UINT* StridePtr()
	{
		return m_stride.get();
	}
	HRESULT Initialize(ID3D11Device* device, T* data, UINT numVertices)
	{
		if (m_buffer.Get() != nullptr)
			m_buffer.Reset();
		m_bufferSize = numVertices;
		if(m_stride.get()==nullptr)
			m_stride = std::make_unique<UINT>(static_cast<UINT>(sizeof(T)));

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;   // default type of buffer
		vertexBufferDesc.ByteWidth = sizeof(T) * numVertices;   // size of buffer
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;   // specify buffer as vertex buffer
		vertexBufferDesc.CPUAccessFlags = 0;   // CPU can't access
		vertexBufferDesc.MiscFlags = 0;   // additional options for buffer

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = data;
		HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_buffer.GetAddressOf());
		if (FAILED(hr))
		{
			ErrorLogger::errorLog(hr, "Failed to create vertex Buffer");
			return hr;
		}
		return hr;
	}
};