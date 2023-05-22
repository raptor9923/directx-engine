#include "KeyboardEvent.h"
KeyboardEvent::KeyboardEvent()   // default constructor
	: m_type(EventType::Invalid), m_key(0u)
{}
KeyboardEvent::KeyboardEvent(const EventType type, const unsigned char key)   // constructor used for creating keyboard events
	:m_type(type),m_key(key)
{}
bool KeyboardEvent::IsPress() const   // state getter
{
	return m_type == EventType::Press;
}
bool KeyboardEvent::IsRelease() const   // state getter
{
	return m_type == EventType::Release;
}
bool KeyboardEvent::IsValid() const   // state getter
{
	return m_type != EventType::Invalid;
}
unsigned char KeyboardEvent::GetKeyCode() const   // key id getter
{
	return m_key;
}
