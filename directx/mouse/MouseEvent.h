#pragma once

struct MousePoint   
{
	int x;
	int y;
};

class MouseEvent  // class that stores information about mouse event
{
public:
	enum class EventType
	{
		LPress,
		LRelease,
		RRelease,
		RPress,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE,
		Invalid,
	};
private:
	EventType m_type;   
	MousePoint m_mousePoint;   
public:
	MouseEvent();   
	MouseEvent(EventType type, const int x, const int y);   
	MouseEvent(EventType type, MousePoint mousePoint);  
	bool IsValid() const;
	EventType GetType() const;
	MousePoint GetPos() const;
	int GetPosX() const;
	int GetPosY() const;
};
