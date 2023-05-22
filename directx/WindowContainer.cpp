#include "WindowContainer.h"
#include <iostream>
#include <memory>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WindowContainer::WindowContainer()
{
	// registering raw input as valid message for window
	static bool raw_input_initialized = false;
	if (raw_input_initialized == false)
	{
		RAWINPUTDEVICE rid;   // defines information for the raw input devices
		ZeroMemory(&rid, sizeof(RAWINPUTDEVICE));
		rid.usUsagePage = 0x01;   // define what kind of devices provide input, 0x01 for generic desktop controllers(mouse,keyboard,gamepad...)
		rid.usUsage = 0x02;   // usage id of device, 0x02 for mouse
		rid.dwFlags = 0;   // flags for specialized interpretation of UsagePage and Usage ID, 0 for default
		rid.hwndTarget = nullptr;   // handle to target window, 0 means that data is send to window which has focus of keyboard

		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		{
			ErrorLogger::errorLog(GetLastError(), "Failed to register input devices");
			exit(-1);
		}
		raw_input_initialized = true;
	}
}

LRESULT WindowContainer::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)   // function handling window messages
{

	if(ImGui_ImplWin32_WndProcHandler(hWnd,uMsg,wParam,lParam))
		return true;
	switch (uMsg)   // uMsg stores message (key or button pressed/released,close window...)
	{
		// keyboard messages
		case WM_KEYDOWN:
		{
			auto keycode = static_cast<unsigned char>(wParam);
			if (m_keyboard.IsKeysAutoRepeat())
			{
				m_keyboard.OnKeyPressed(keycode);
			}
			else
			{
				const bool wasPressed = lParam & KF_REPEAT;    // check last state of key (1 if down)
				if (!wasPressed)
				{
					m_keyboard.OnKeyPressed(keycode);
				}
			}
			return 0;
		}
		case WM_KEYUP:
		{
			auto keycode = static_cast<unsigned char>(wParam);
			m_keyboard.OnKeyReleased(keycode);
			return 0;
		}
		// char message
		case WM_CHAR:
		{
			auto ch = static_cast<unsigned char>(wParam);
			if (m_keyboard.IsCharsAutoRepeat())
			{
				m_keyboard.OnChar(ch);
			}
			else
			{
				const bool wasPressed = lParam & KF_REPEAT;    
				if (!wasPressed)
				{
					m_keyboard.OnChar(ch);
				}
			}
			return 0;
		}
		// mouse messages
		case WM_MOUSEMOVE:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };   // low order word specifies x-coordinate and high order word specifies y-coordinate
			m_mouse.OnMouseMove(mousePoint);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };
			m_mouse.OnLeftPressed(mousePoint);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };
			m_mouse.OnRightPressed(mousePoint);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };
			m_mouse.OnMiddlePressed(mousePoint);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };
			m_mouse.OnMiddleReleased(mousePoint);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };
			m_mouse.OnRigthReleased(mousePoint);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };
			m_mouse.OnLeftReleased(mousePoint);
			return 0;
		}
		case WM_MOUSEHWHEEL:
		{
			MousePoint mousePoint{ LOWORD(lParam),HIWORD(lParam) };
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				m_mouse.OnWheelUp(mousePoint);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			{
				m_mouse.OnWheelDown(mousePoint);
			}
			break;
		}
		// raw input message
		case WM_INPUT:
		{
			UINT dataSize{ 0 };
			GetRawInputData(std::bit_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &dataSize, sizeof(RAWINPUTHEADER));   // obtain size of data
			
			if (dataSize <= 0)   // check if no data
				return DefWindowProc(hWnd, uMsg, wParam, lParam);

			std::vector<BYTE> rawData(dataSize);
			if (GetRawInputData(std::bit_cast<HRAWINPUT>(lParam), RID_INPUT, rawData.data(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)   // populate data 
			{
				const RAWINPUT* rawInput = std::bit_cast<RAWINPUT*>(rawData.data());
				if (rawInput->header.dwType == RIM_TYPEMOUSE)
				{
					MousePoint mousePoint{ static_cast<int>(rawInput->data.mouse.lLastX),static_cast<int>(rawInput->data.mouse.lLastY) };
					m_mouse.OnMouseMoveRaw(mousePoint);
				}
			}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

