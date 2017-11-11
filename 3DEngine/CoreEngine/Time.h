#pragma once

#include <chrono>

namespace D3DEngine
{
	class Time
	{
	public:
		Time();
		~Time();

		long GetTime();

		const static long SECOND = 1000000000L;
	};
}