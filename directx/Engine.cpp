#include "Engine.h"
using namespace DirectX;
bool Engine::Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height)
{
	m_timer.Start();
	// initialize window
	if (!m_window.Initialize(this, hInstance, windowTitle, windowClass, width, height))
		return false;
	// initialize graphics
	if (!m_gfx.Initialize(m_window.GetHWND(), width, height))
		return false;
	return true;
}

bool Engine::ProcessMessages()
{
	return m_window.ProcessMessages();
}

void Engine::Update()
{

	float timeDelta = m_timer.GetMilisecondsElapsed();
	m_timer.Restart();
	while (!m_keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent keyboardEvent = m_keyboard.ReadKey();
		unsigned char keycode = keyboardEvent.GetKeyCode();
	}
	while (!m_keyboard.CharBufferIsEmpty())
	{
		unsigned char character = m_keyboard.ReadChar();
	}
	while (!m_mouse.EventBufferIsEmpty())
	{
		constexpr float mouseCameraSpeed = 0.005f;
		MouseEvent mouseEvent= m_mouse.ReadEvent();
		if (mouseEvent.GetType() == MouseEvent::EventType::RAW_MOVE)
			m_gfx.AccesCamera()->AdjustRotation(static_cast<float>(mouseEvent.GetPosY())* mouseCameraSpeed, static_cast<float>(mouseEvent.GetPosX()) * mouseCameraSpeed, 0);
	}
	const float cameraSpeed = 0.005f*timeDelta;
	if (m_keyboard.KeyIsPressed('W'))
		m_gfx.AccesCamera()->AdjustPosition(m_gfx.AccesCamera()->GetForwardVector() * cameraSpeed);
	if (m_keyboard.KeyIsPressed('S'))
		m_gfx.AccesCamera()->AdjustPosition(m_gfx.AccesCamera()->GetBackwardVector() * cameraSpeed);
	if (m_keyboard.KeyIsPressed('A'))
		m_gfx.AccesCamera()->AdjustPosition(m_gfx.AccesCamera()->GetLeftVector() * cameraSpeed);
	if (m_keyboard.KeyIsPressed('D'))
		m_gfx.AccesCamera()->AdjustPosition(m_gfx.AccesCamera()->GetRightVector() * cameraSpeed);
	if (m_keyboard.KeyIsPressed(VK_SPACE))
		m_gfx.AccesCamera()->AdjustPosition(0.0f,cameraSpeed,0.0f);
	if (m_keyboard.KeyIsPressed('Z'))
		m_gfx.AccesCamera()->AdjustPosition(0.0f, -cameraSpeed, 0.0f);
}

void Engine::RenderFrame()   // updates screen
{
	m_gfx.RenderFrame();
}