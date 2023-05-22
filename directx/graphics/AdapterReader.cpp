#include "AdapterReader.h"


std::vector<AdapterData> AdapterReaders::GetAdapterData()   // returns vector of graphics adapters
{
	if (!m_adapters.empty())   // If already initialized
		return m_adapters;
	Microsoft::WRL::ComPtr<IDXGIFactory> factoryPtr;   
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), std::bit_cast<void**>(factoryPtr.GetAddressOf()));    // generate unique id and create DXGIFactory
	if (FAILED(hr))  
	{
		ErrorLogger::errorLog(hr, "Failed to create DXGIFactory for enumerating adapters.");
		exit(-1);
	}
	IDXGIAdapter* adapterPtr;
	UINT index = 0;
	while (SUCCEEDED(factoryPtr->EnumAdapters(index, &adapterPtr)))   // enumerate adapters
	{
		m_adapters.emplace_back(adapterPtr);
		index += 1;
	}
	return m_adapters;   // return filled vector
}

AdapterData::AdapterData(IDXGIAdapter* adapterPtr) :
	m_adapter{adapterPtr}
{
	HRESULT hr = adapterPtr->GetDesc(&m_description);
	if (FAILED(hr))
	{
		ErrorLogger::errorLog(hr, "Failed to get description for IDXGIAdapter.");
	}
}

IDXGIAdapter* AdapterData::GetAdapter()
{
	return m_adapter.Get();
}
