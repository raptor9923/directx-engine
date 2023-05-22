#pragma once

class KeyboardEvent   // class storing information about keyboard events
{
public:
	enum class EventType   
	{
		Press,
		Release,
		Invalid,
	};
private:
	EventType m_type;   // state of key
	unsigned char m_key;   // key id

public:
	KeyboardEvent();   // default constructor
	KeyboardEvent(const EventType type, const unsigned char key);   // construtor use when creaitng events
	bool IsPress() const;     //
	bool IsRelease() const;   // getters for key state
	bool IsValid() const;     //
	unsigned char GetKeyCode() const;  // getter for key id

};

