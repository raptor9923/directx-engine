#pragma once
#include"KeyboardEvent.h"
#include<queue>
#include<array>

class KeyboardClass   // class storing keyboard events and options
{
	bool m_autoRepeatKeys{ false };   // set true for constat input when holding key
	bool m_autoRepeatChars{ false };   // set true for constat input of chars when holding key
	std::array <bool, 256> m_keyStates{ false }; 
	std::queue<KeyboardEvent> m_keyBuffer; 
	std::queue<unsigned char> m_charBuffer;  
public:

	bool KeyIsPressed(const unsigned char keycode) const;   
	bool KeyBufferIsEmpty() const;
	bool CharBufferIsEmpty() const;
	KeyboardEvent ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChar();
	void DisableAutoRepeatChar();
	bool IsKeysAutoRepeat() const;
	bool IsCharsAutoRepeat() const;
};

