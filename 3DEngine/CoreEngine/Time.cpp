#include "Time.h"

namespace D3DEngine
{
	Time::Time()
	{
	}

	Time::~Time()
	{

	}

	long Time::GetTime()
	{
		auto Now = std::chrono::system_clock::now();
		auto Now_NS = std::chrono::time_point_cast<std::chrono::nanoseconds>(Now);
		auto Epoch = Now_NS.time_since_epoch();
		auto Value = std::chrono::duration_cast<std::chrono::nanoseconds>(Epoch);
		long Duration = Value.count();
		return Duration;
	}

	double Time::GetDelta() const
	{
		return m_Delta;
	}

	void Time::SetDelta(double Delta)
	{
		m_Delta = Delta;
	}
}