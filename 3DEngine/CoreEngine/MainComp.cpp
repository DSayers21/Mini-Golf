//Includes
#include "MainComp.h"

namespace D3DEngine
{
	MainComp::MainComp(std::string Title, int Width, int Height, int FrameRate, MainGame* Game)
	{
		//Init Core Aspects
		m_Window = new D3DEngine::Window();
		m_Window->Init(Title, Width, Height);
		m_Input = new GetInput(m_Window);
		m_Time = new Time();

		//Setup Game
		m_Game = Game;
		m_Game->SetWindow(m_Window);
		m_Game->SetEngine(this);

		//Setup Frame Rate
		m_Game->SetTime(m_Time);
		m_FrameTime = 1.0 / FrameRate;		
		m_FrameCap = FrameRate;

		//Init Render Engine
		m_RenderEngine = new D3DEngine::RenderEngine(m_Window);

		//Init Physics Engine
		m_PhysicsEngine = new D3DEngine::PhysicsEngine();
	
		//Start MainComp
		Start();
	}

	MainComp::~MainComp()
	{
		//Delete all aspects
		delete m_Game;
		delete m_Window;
		delete m_Input;
		delete m_RenderEngine;
		delete m_PhysicsEngine;
		delete m_Time;
	}

	void MainComp::Start()
	{
		//Run the main game loop
		Run();
	}

	void MainComp::Stop()
	{
		//Empty
	}

	void MainComp::Run()
	{
		//Prepare game time system
		long StartTime;
		long LastTime = m_Time->GetTime();
		long PassedTime;
		double UnproccessedTime = 0;
		//Keep track of the frames per second
		int Frames = 0;
		long FrameCounter = 0;
		//If the game needs to be rendered or not
		bool Render = false;
		//Init the game
		m_Game->Init(m_RenderEngine, m_PhysicsEngine);
		//Add the title text to the rendering engine
		m_RenderEngine->AddText("TITLE", TextToRender("Mini-Golf Game", Vector3f(255, 255, 255), m_Window->GetWidth()-175, m_Window->GetHeight() - 24));

		//While the window is open
		while (!m_Window->IsClosed())
		{
			Render = false;												//Set render to false
			//Update time
			StartTime = m_Time->GetTime();
			PassedTime = StartTime - LastTime;
			LastTime = StartTime;
			UnproccessedTime += PassedTime / (double)m_Time->SECOND;
			//Increase frame counter by passed time since last loop
			FrameCounter += PassedTime;
			//While the unprocessed time is grater than the max FPS
			while (UnproccessedTime > m_FrameTime)
			{
				//Set render to true
				Render = true;
				UnproccessedTime -= m_FrameTime;		//Reduce the unproccessed time
				//Update The Game
				m_Game->Input(m_Input, m_FrameTime);
				//Check if the mouse needs to be warped
				if (m_Input->GetIsWarpMouse())
				{
					//Warp the mouse
					m_Window->Warp(m_Input->GetWarpMousePos()); 
					//Set mouse warp to false
					m_Input->SetIsWarpMouse(false);
				}
				//Check if the window is closed, if it is close it
				if (m_Input->GetIsClosed()) m_Window->Close();

				//Update the game
				m_Game->Update(m_FrameTime);

				//Check if the current frame counter is greater than or equal to a second of time
				if (FrameCounter >= m_Time->SECOND)
				{
					//Update the FPS counters
					std::string FPS = "Current FPS: " + std::to_string(Frames) + "/" + std::to_string(m_FrameCap);
					//Update the text in the rendering engine to display the current FPS
					m_RenderEngine->AddText("FPS", TextToRender(FPS, Vector3f(0, 255, 255), 5, m_Window->GetHeight()-24));
					//Reset to 0
					Frames = 0;
					FrameCounter = 0;
				}
			}
			//If the game needs to be rendered
			if (Render)
			{
				//Render the game
				m_Game->Draw(m_RenderEngine);
				//Update the window
				m_Window->Update();
				//Increase the frames by one
				Frames++;
			}
		}
	}

	void MainComp::Destroy()
	{
		//Empty
	}
}