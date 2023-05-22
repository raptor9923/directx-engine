#include"Timer.h"

Timer::Timer() =default;

float Timer::GetMilisecondsElapsed() const
{
	if (m_isRunning)
	{
		auto elapsed = static_cast<float>(std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_start).count());
		return elapsed;
	}
	else
	{
		auto elapsed = static_cast<float>(std::chrono::duration<double, std::milli>(m_stop - m_start).count());
		return elapsed;
	}
}
void Timer::Restart()
{
	m_isRunning = true;
	m_start = std::chrono::high_resolution_clock::now();
}
bool Timer::Stop()
{
	if (!m_isRunning)
		return false;
	else
	{
		m_stop = std::chrono::high_resolution_clock::now();
		m_isRunning = false;
		return true;
	}
}
bool Timer::Start()
{
	if (m_isRunning)
		return false;
	else
	{
		m_stop = std::chrono::high_resolution_clock::now();
		m_isRunning = true;
		return true;
	}
}