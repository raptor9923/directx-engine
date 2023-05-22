#include "WindowContainer.h"

bool Window::Initialize(WindowContainer* pWindowContainer,HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height)   
{
	m_hInstnace = hInstance;
	m_width = width;
	m_height = height;
	m_windowTitle = windowTitle;
	m_wideWindowTitle = StringConverter::stringConverter(windowTitle);   
	m_windowClass = windowClass;
	m_wideWindowClass = StringConverter::stringConverter(windowClass);   
	RegisterWindowClass();

	//center window
	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - m_width / 2;   
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - m_height / 2;
	RECT wr;
	wr.left = centerScreenX;
	wr.top = centerScreenY;
	wr.right = wr.left + m_width;
	wr.bottom = wr.top + m_height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false);   // adjust window dimensions so border doesn't count

	m_handle = CreateWindowEx(
		0,   // additional window styles
		m_wideWindowClass.c_str(),   // window class name
		m_wideWindowTitle.c_str(),   // window title name
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,   // styles of window ( title bar, minimize button, window menu)
		wr.left,   // initial horizontal position
		wr.top,   // initial vertical position
		wr.right - wr.left,   // width
		wr.bottom - wr.top,   // height
		nullptr,   // handle to parent window
		nullptr,   // handle to menu
		m_hInstnace,   // handle to instance of windows's module
		pWindowContainer); // pointer to WindowContainer is send through CREATESTRUCT when window is created);    

	if (m_handle == nullptr)    	{
		ErrorLogger::errorLog(GetLastError(), "CreateWindowEx Failed for window: " + this->m_windowTitle);
		return false;
	}

	ShowWindow(m_handle, SW_SHOW);   
	SetForegroundWindow(m_handle);   // set to first plane
	SetFocus(m_handle);   // sets keyboard focus to specified window

	return true;
}

bool Window::ProcessMessages()   // function for processing messages
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));   
	while (PeekMessage(&msg,m_handle, 0, 0, PM_REMOVE))   // check for messages, 0,0 for no filters, removes the message from queue
	{
		TranslateMessage(&msg);   // translate to character message
		DispatchMessage(&msg);   
	}
	if (msg.message == WM_NULL && !IsWindow(m_handle))   // check if window exists and if messages are empty (window is closed)
	{
	
		m_handle = nullptr;   
		UnregisterClass(m_wideWindowClass.c_str(),m_hInstnace);   
		return false;   

	}
	return true;
}

HWND Window::GetHWND() const 
{
	return m_handle;
}



Window::~Window()  
{
	if (m_handle)
	{
		UnregisterClass(m_wideWindowClass.c_str(),m_hInstnace);
		DestroyWindow(m_handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)   // redirects messages from window to WindowContainer
{
	if (uMsg == WM_CLOSE)   // close window
	{
		DestroyWindow(hwnd);
		return 0;
	}
	else   // redirect all default messages to WindowContainer
	{
		auto const pWindow = std::bit_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));   //retrieve WindowContainer pointer from USERDATA attribute of window
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);   // call WindowContainer's WNDPROC function
	}

}
LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)   // WNDPROC function which setups messages to sent them to WindowContainer
{

 	if(uMsg== WM_NCCREATE)   // window is first created
	{
		const CREATESTRUCTW* const pCreate = std::bit_cast<CREATESTRUCTW*>(lParam);   // CREASTESTRUCTW holds pointer to WindowContainer, which was passed as argument when CreateWindowEX was called
		auto windowContainerPtr = std::bit_cast<WindowContainer*>(pCreate->lpCreateParams);   // access the pointer 
		if (!windowContainerPtr)
		{
			ErrorLogger::errorLog("Critical Error: pointer to window container is null during WM_NCCREATE.");  
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, std::bit_cast<LONG_PTR>(windowContainerPtr));   // store pointer to WindowContainer in USERDATA attribute of window
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, std::bit_cast<LONG_PTR>(&HandleMsgRedirect));   // change WNDPROC function to HandleMsgRedirect
		return windowContainerPtr->WindowProc(hwnd, uMsg, wParam, lParam);   
	}
	else   
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



void Window::RegisterWindowClass() 
{	
	WNDCLASSEX wc;   
	wc.cbSize = sizeof(WNDCLASSEX);  // size 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;   // window class styles
	wc.lpfnWndProc = HandleMessageSetup;   // WNDPROC function 
	wc.cbClsExtra = 0;   // allocate additional bytes
	wc.cbWndExtra = 0;   // allocate additional bytes
	wc.hInstance =m_hInstnace;   // handle to window instance 
	wc.hIcon = nullptr;   // handle to window icon, nullptr for default icon
	wc.hIconSm = nullptr;   // handle to small window icon, nullptr for  
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);   // handle to cursor, set to default arrow
	wc.hbrBackground = nullptr;  // handle to background brush,
	wc.lpszMenuName = nullptr;  // handle to resource name of menu
	wc.lpszClassName = m_wideWindowClass.c_str(); // handle to class name c string

	if (!RegisterClassEx(&wc))
	{
		ErrorLogger::errorLog("RegisterClassEx failed");
	}
}