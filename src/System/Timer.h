#pragma once

#include <functional>

class Timer
{
public:
	Timer();

	void update(const double);
	void start(const double);
	void setCallback(std::function<void()>);

private:
	std::function<void()> m_callback;
	double m_timeLeft;
	bool m_isRunning;
};