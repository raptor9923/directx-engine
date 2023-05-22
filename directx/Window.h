#pragma once
#include"ErrorLogger.h"

class WindowContainer;

class Window   // window class
{
	HWND m_handle = nullptr;  
	HINSTANCE m_hInstnace = nullptr;
	std::string m_windowTitle = "";
	std::wstring m_wideWindowTitle = L"";
	std::string m_windowClass = "";
	std::wstring m_wideWindowClass = L"";
	int m_width{};
	int m_height{};

	void RegisterWindowClass(); 

public:

	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height);   
	bool ProcessMessages();   
	HWND GetHWND() const;   
	~Window();
};
