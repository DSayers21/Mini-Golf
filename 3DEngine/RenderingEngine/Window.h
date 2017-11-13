#pragma once

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
		Window();
		~Window();

		void Init(std::string& Title, int Width, int Height);

		void SwapBuffers();

		void Update();

		void Close();

		void Warp(Vector2f WarpPos);

		//Getters
		bool IsClosed() { return m_isClosed; }
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		Vector2f GetCenter() { return Vector2f(m_Width / 2, m_Height / 2); }

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_glContext;
		bool m_isClosed;

		int m_Width, m_Height;
	};
}