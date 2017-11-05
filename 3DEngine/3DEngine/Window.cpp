#include "Window.h"
#include <GL/glew.h>

namespace D3DEngine
{
	Window::Window()
	{
		m_Width = 0;
		m_Height = 0;
		m_isClosed = false;
	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Window::Init(std::string& Title, int Width, int Height)
	{
		m_Width = Width;
		m_Height = Height;
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL);
		m_glContext = SDL_GL_CreateContext(m_Window);

		GLenum Status = glewInit();
		if (Status != GLEW_OK)
		{
			std::cerr << "Glew Failed to Initalise" << std::endl;
		}

		RenderUtil::InitGraphics();
	}

	void Window::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_Window);
	}

	void Window::Update()
	{
		SDL_GL_SwapWindow(m_Window);
	}

	void Window::Clear()
	{
		RenderUtil::ClearScreen();
	}

	void Window::Close()
	{
		m_isClosed = true;
	}
}