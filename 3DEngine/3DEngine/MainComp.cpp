#include "MainComp.h"

namespace D3DEngine
{
	MainComp::MainComp(D3DEngine::Window& window)
	{
		m_Window = &window;
		m_Game = new MainGame(m_Window);
	}

	MainComp::~MainComp()
	{

	}

	void MainComp::Start()
	{
		Run();
	}

	void MainComp::Stop()
	{

	}

	void MainComp::Run()
	{
		long StartTime;
		long LastTime = m_Time.GetTime();
		long PassedTime;
		double UnproccessedTime = 0;
		double FrameTime = 1.0 / m_FrameCap;
		bool Render = false;
		int Frames = 0;
		long FrameCounter = 0;

		while (!m_Window->IsClosed())
		{
			Render = false;
			StartTime = m_Time.GetTime();
			PassedTime = StartTime - LastTime;
			LastTime = StartTime;
			UnproccessedTime += PassedTime / (double)m_Time.SECOND;
			FrameCounter += PassedTime;

			while (UnproccessedTime > FrameTime)
			{
				Render = true;
				UnproccessedTime -= FrameTime;
				//Update The Game
				m_Game->Input();
				m_Game->Update();

				if (FrameCounter >= m_Time.SECOND)
				{
					std::cout << Frames << std::endl;
					Frames = 0;
					FrameCounter = 0;
				}

			}
			if (Render)
			{
				Draw();
				Frames++;
			}
		}
	}

	void MainComp::Draw()
	{
		m_Window->Clear();

		m_Game->Draw();
		m_Window->Update();
	}

	void MainComp::Destroy()
	{

	}
}