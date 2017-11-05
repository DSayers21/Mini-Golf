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
		double GetDelta();
		void SetDelta(double Delta);

		const static long SECOND = 1000000000L;
	private:
		double m_Delta;
	};
}