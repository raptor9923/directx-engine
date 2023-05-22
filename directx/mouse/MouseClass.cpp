#include "MouseClass.h"

void MouseClass::OnLeftPressed(MousePoint mousePoint)
{
	m_leftIsDown = true;
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::LPress,mousePoint)});
}
void MouseClass::OnLeftReleased(MousePoint mousePoint)
{
	m_leftIsDown = false;
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::LRelease,mousePoint) });
}
void MouseClass::OnRightPressed(MousePoint mousePoint)
{
	m_rightIsDown = true;
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::RPress,mousePoint) });
}
void MouseClass::OnRigthReleased(MousePoint mousePoint)
{
	m_rightIsDown = false;
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::RRelease,mousePoint) });
}
void MouseClass::OnMiddlePressed(MousePoint mousePoint)
{
	m_middleButtomIsDown = true;
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::MPress,mousePoint) });
}
void MouseClass::OnMiddleReleased(MousePoint mousePoint)
{
	m_middleButtomIsDown = false;
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::MRelease,mousePoint) });
}
void MouseClass::OnWheelUp(MousePoint mousePoint)
{
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::WheelUp,mousePoint) });
}
void MouseClass::OnWheelDown(MousePoint mousePoint)
{
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::WheelDown,mousePoint) });
}
void MouseClass::OnMouseMove(MousePoint mousePoint)
{
	m_mousePoint = mousePoint;
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::Move,mousePoint) });
}
void MouseClass::OnMouseMoveRaw(MousePoint mousePoint)
{
	m_eventBuffer.push({ MouseEvent(MouseEvent::EventType::RAW_MOVE,mousePoint) });
}
bool MouseClass::IsLeftDown() const
{
	return m_leftIsDown;
}
bool MouseClass::IsMiddleDown() const
{
	return m_middleButtomIsDown;
}
bool MouseClass::IsRightDown() const
{
	return m_rightIsDown;
}
int MouseClass::GetPosX() const
{
	return m_mousePoint.x;
}
int MouseClass::GetPosY() const
{
	return m_mousePoint.y;
}
MousePoint MouseClass::GetPos() const
{
	return m_mousePoint;
}
bool MouseClass::EventBufferIsEmpty() const
{
	return m_eventBuffer.empty();
}
MouseEvent MouseClass::ReadEvent() 
{
	if (m_eventBuffer.empty())
		return MouseEvent();
	else
	{
		MouseEvent event = m_eventBuffer.front();
		m_eventBuffer.pop();
		return event;
	}
}