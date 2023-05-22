#pragma once
#include "WindowContainer.h"
#include "Timer.h"
class Engine : public WindowContainer   // class that processes messages and engine
{
	Timer m_timer;
public:
	bool Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height);
	bool ProcessMessages();
	void Update();
	void RenderFrame();
};
