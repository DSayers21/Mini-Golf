#include "MainComp.h"

namespace D3DEngine
{
	MainComp::MainComp(std::string Title, int Width, int Height, int FrameRate, MainGame* Game)
	{
		m_Window = new D3DEngine::Window();
		m_Window->Init(Title, Width, Height);
		m_Input = new GetInput();
		m_Game = Game;
		m_Game->SetWindow(m_Window);
		m_Game->SetTime(m_Time);
		m_FrameTime = 1.0 / FrameRate;		

		m_RenderEngine = new D3DEngine::RenderEngine();

		Start();
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
		long LastTime = m_Time->GetTime();
		long PassedTime;
		double UnproccessedTime = 0;
		bool Render = false;
		int Frames = 0;
		long FrameCounter = 0;
		m_Game->Init();

		while (!m_Window->IsClosed())
		{
			Render = false;
			StartTime = m_Time->GetTime();
			PassedTime = StartTime - LastTime;
			LastTime = StartTime;
			UnproccessedTime += PassedTime / (double)m_Time->SECOND;
			FrameCounter += PassedTime;

			while (UnproccessedTime > m_FrameTime)
			{
				Render = true;
				UnproccessedTime -= m_FrameTime;
				//Update The Game
				m_Game->Input(m_Input, m_FrameTime);
				if (m_Input->GetIsClosed()) m_Window->Close();
				m_Game->Update(m_FrameTime);

				if (FrameCounter >= m_Time->SECOND)
				{
					std::cout << Frames << std::endl;
					Frames = 0;
					FrameCounter = 0;
				}

			}
			if (Render)
			{
				m_RenderEngine->Render(m_Game->GetRootObject());
				m_Window->Update();

				Frames++;
			}
		}
	}

	void MainComp::Destroy()
	{

	}
}