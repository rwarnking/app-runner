///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: timer.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "../header/timer.h"


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////


void Timer::Initialize()
{
	// Check if the system support high frequency timers
	// TODO this may not work on linux
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_frequency));

	// Calculate the number of ticks per millisecond
	constexpr float MS_PER_S = 1000.0F;
	m_ticksPerMS = float(m_frequency / MS_PER_S);

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_startTime));
}


void Timer::Frame()
{
	INT64 currentTime{ 0 };

	// Check the current time and then calculate the difference
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));

	auto timeDifference = float(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMS;

	m_startTime = currentTime;
}


auto Timer::GetTime() const -> float
{
	return m_frameTime;
}
