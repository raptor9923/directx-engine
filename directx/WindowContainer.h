#pragma once
#include "Window.h"
#include "keyboard/KeyboardClass.h"
#include"mouse/MouseClass.h"
#include"graphics/Graphics.h"

class WindowContainer   // class that handle window messages
{
protected:
	Window  m_window;
	KeyboardClass m_keyboard;
	MouseClass m_mouse;
	Graphics m_gfx;
public:
	WindowContainer();
	LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// function handling window messages
};
