#pragma once

//Includes
#include <chrono>

namespace D3DEngine
{
	class Time
	{
	public:
		//Constructor
		Time();
		//Destructor
		~Time();

		//Getters
		long GetTime();

		//Length of a second
		const static long SECOND = 1000000000L;
	};
}