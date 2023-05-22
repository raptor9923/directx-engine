#include "KeyboardClass.h"

bool KeyboardClass::KeyIsPressed (const unsigned char keycode) const	
{
	return m_keyStates[keycode];
}

bool KeyboardClass::KeyBufferIsEmpty() const
{
	return m_keyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty() const
{
	return m_charBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if (m_keyBuffer.empty())   
		return KeyboardEvent();
	else
	{
		KeyboardEvent event = m_keyBuffer.front();
		m_keyBuffer.pop();
		return event;
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (m_charBuffer.empty())
		return 0u;
	else
	{
		unsigned char a = m_charBuffer.front();
		m_charBuffer.pop();
		return a;
	}
}

void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	m_keyStates[key] = true;
	m_keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	m_keyStates[key] = false;
	m_keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	m_charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	m_autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	m_autoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChar()
{
	m_autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatChar()
{
	m_autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat() const
{
	return m_autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat() const
{
	return m_autoRepeatChars;
}