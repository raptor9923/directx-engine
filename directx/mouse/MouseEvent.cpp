#include "MouseEvent.h"


MouseEvent::MouseEvent()   
	:m_type{ MouseEvent::EventType::Invalid }, m_mousePoint{ 0 , 0 }
{}

MouseEvent::MouseEvent(EventType type, int x, int y)  
	:m_type{ type }, m_mousePoint{ x,y }
{}

MouseEvent::MouseEvent(EventType type, MousePoint mousePoint)  
	:m_type{ type }, m_mousePoint{ mousePoint }
{}

bool MouseEvent::IsValid() const
{
	return m_type != EventType::Invalid;
}
MouseEvent::EventType MouseEvent::GetType() const
{
	return m_type;
}
MousePoint MouseEvent::GetPos() const
{
	return m_mousePoint;
}
int MouseEvent::GetPosX() const
{
	return m_mousePoint.x;
}
int MouseEvent::GetPosY() const
{
	return m_mousePoint.y;
}

