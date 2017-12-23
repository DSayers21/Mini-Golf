#pragma once

//Includes
#include <tchar.h>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>

#include "Vector2f.h"

namespace D3DEngine
{
	class Window
	{
	public:
		//Constructor
		Window();
		//Destructor
		~Window();
		//Init the window
		void Init(std::string& Title, int Width, int Height);
		//Swap the buffers
		void SwapBuffers();
		//Update the window
		void Update();
		//Close the window
		void Close();
		//Warp the mouse to a position
		void Warp(Vector2f WarpPos);

		//Getters
		inline bool IsClosed() { return m_isClosed; }
		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }
		inline Vector2f GetCenter() { return Vector2f(m_Width / 2, m_Height / 2); }
		inline SDL_Window* GetSDLWindow() { return m_Window; }

	private:
		SDL_Window* m_Window;		//Pointer to the SDL window
		SDL_GLContext m_glContext;	//Ponter to the gl context

		bool m_isClosed;			//If the window has been closed

		int m_Width, m_Height;		//Width and height of the windoe
	};
}