#include "Timer.h"

namespace HT
{
	Timer::Timer() :
		start_time{ Clock::now() },
		previous_tick{ Clock::now() }
	{
	}

	void Timer::Start()
	{
		if (!running)
		{
			running = true;
			start_time = Clock::now();
		}
	}

	void Timer::Lap()
	{
		lapping = true;
		lap_time = Clock::now();
	}

	bool Timer::IsRunning() const
	{
		return running;
	}
}
