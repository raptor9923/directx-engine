#pragma once
#include"MouseEvent.h"
#include<queue>
class MouseClass   // class storing information about mouse events and mouse state
{
	std::queue<MouseEvent> m_eventBuffer;
	bool m_leftIsDown = false;
	bool m_rightIsDown = false;
	bool m_middleButtomIsDown = false;
	MousePoint m_mousePoint = { 0,0 };
public:
	void OnLeftPressed(MousePoint mousePoint);
	void OnLeftReleased(MousePoint mousePoint);
	void OnRightPressed(MousePoint mousePoint);
	void OnRigthReleased(MousePoint mousePoint);
	void OnMiddlePressed(MousePoint mousePoint);
	void OnMiddleReleased(MousePoint mousePoint);
	void OnWheelUp(MousePoint mousePoint);
	void OnWheelDown(MousePoint mousePoint);
	void OnMouseMove(MousePoint mousePoint);
	void OnMouseMoveRaw(MousePoint mousePoint);
	bool IsLeftDown() const;
	bool IsMiddleDown() const;
	bool IsRightDown() const;
	int GetPosX() const;
	int GetPosY() const;
	MousePoint GetPos() const;
	bool EventBufferIsEmpty() const;
	MouseEvent ReadEvent();
};
