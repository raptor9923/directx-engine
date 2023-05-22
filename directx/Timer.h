#pragma once
#include<chrono>

class Timer
{
	bool m_isRunning{ false };
	std::chrono::time_point<std::chrono::steady_clock> m_start{ std::chrono::high_resolution_clock::now() };
	std::chrono::time_point<std::chrono::steady_clock> m_stop{ std::chrono::high_resolution_clock::now() };
public:
	Timer();
	float GetMilisecondsElapsed() const;
	void Restart();
	bool Stop();
	bool Start();

};