//Includes
#include "Time.h"

namespace D3DEngine
{
	Time::Time()
	{
		//Empty
	}

	Time::~Time()
	{
		//Empty
	}

	long Time::GetTime()
	{
		//Get current time, and convert it into correct form
		auto Now = std::chrono::system_clock::now();
		auto Now_NS = std::chrono::time_point_cast<std::chrono::nanoseconds>(Now);
		auto Epoch = Now_NS.time_since_epoch();
		auto Value = std::chrono::duration_cast<std::chrono::nanoseconds>(Epoch);
		long Duration = Value.count();
		//Return the time
		return Duration;
	}
}