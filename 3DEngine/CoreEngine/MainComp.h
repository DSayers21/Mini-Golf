#pragma once

//Includes
#include "Window.h"
#include "Time.h"
#include "Input.h"
#include <iostream>
#include "MainGame.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"

namespace D3DEngine
{
	class MainComp
	{
	public:
		//Constructor
		MainComp(const std::string& Title, int Width, int Height, int FrameRate, MainGame* Game);
		//Destructor
		~MainComp();
		//Start the main component
		void Start();
		//Stop the main component
		void Stop();

		//Getters
		inline RenderEngine* GetRenderEngine() { return m_RenderEngine; }
		inline PhysicsEngine* GetPhysicsEngine() { return m_PhysicsEngine; }
	private:
		//Start the main game logic loop
		void Run();
		//Destroy the main component
		void Destroy();

		Window* m_Window;						//Pointer to the window
		double m_FrameCap = 5000.0;				//Set basic value for the frame rate cap
		double m_FrameTime;						//Current FPS
		Time* m_Time;							//Time object to keep track of game time
		MainGame* m_Game;						//Pointer to the game
		RenderEngine* m_RenderEngine;			//Pointer to the rendering engine
		PhysicsEngine* m_PhysicsEngine;			//Pointer to the physics engine
		GetInput* m_Input;						//Pointer to the input handeler
	};
}