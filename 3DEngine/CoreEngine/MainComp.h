#pragma once

#include "Window.h"
#include "Time.h"
#include "Input.h"
#include <iostream>
#include "MainGame.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	class MainComp
	{
	public:
		MainComp(std::string Title, int Width, int Height, int FrameRate, MainGame* Game);
		~MainComp();

		void Start();
		void Stop();

	private:
		void Run();
		void Destroy();

		Window* m_Window;
		double m_FrameCap = 5000.0;
		double m_FrameTime;
		Time* m_Time;
		MainGame* m_Game;
		RenderEngine* m_RenderEngine;
		Input* m_Input;
	};
}
