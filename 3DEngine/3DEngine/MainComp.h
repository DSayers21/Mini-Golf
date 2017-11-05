#pragma once

#include "Window.h"
#include "Time.h"
#include <iostream>
#include "MainGame.h"

namespace D3DEngine
{
	class MainComp
	{
	public:
		MainComp(D3DEngine::Window& window);
		~MainComp();

		void Start();
		void Stop();

	private:
		void Run();
		void Draw();
		void Destroy();

		Window* m_Window;
		double m_FrameCap = 5000.0;
		Time m_Time;
		MainGame* m_Game;
	};
}
