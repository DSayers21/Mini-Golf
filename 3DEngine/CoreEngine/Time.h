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
		double GetDelta() const;
		void SetDelta(double Delta);

		const static long SECOND = 1000000000L;

		double m_Delta = 0;
	};
}