#pragma once
#include <wrl/client.h>
#include <vector>
#include <d3d11.h>
#include"../ErrorLogger.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib,"DXGI.lib")
class AdapterData   // class that hold graphics cards data
{	
	DXGI_ADAPTER_DESC m_description;   
	Microsoft::WRL::ComPtr<IDXGIAdapter> m_adapter;
public:
	explicit AdapterData(IDXGIAdapter* adapterPtr); 
	IDXGIAdapter* GetAdapter();
};


class AdapterReaders   // class that finds graphic cards
{
	inline static std::vector<AdapterData> m_adapters;
public:
	static std::vector<AdapterData> GetAdapterData();   // static in case of multiple windows
};

