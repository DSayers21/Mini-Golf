//Includes
#include "Window.h"
#include <GL/glew.h>

namespace D3DEngine
{
	Window::Window() :
		m_Width(0), m_Height(0), m_isClosed(false)
	{
		//Empty
	}

	Window::~Window()
	{
		//Delete the context
		SDL_GL_DeleteContext(m_glContext);
		//Destroy the window
		SDL_DestroyWindow(m_Window);
		//Quit SDL
		SDL_Quit();
	}

	void Window::Init(std::string& Title, int Width, int Height)
	{
		//Set the width and height
		m_Width = Width;
		m_Height = Height;

		//Init SDL everything
		SDL_Init(SDL_INIT_EVERYTHING);

		//Setup colours for SDL
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//Create the sdl window
		m_Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL);
		//Create the gl context from the window
		m_glContext = SDL_GL_CreateContext(m_Window);

		//Get the status of glewinit, if not okay then display message
		GLenum Status = glewInit();
		if (Status != GLEW_OK)
			std::cerr << "Glew Failed to Initalise" << std::endl;
	}

	void Window::SwapBuffers()
	{
		//Swap the buffers
		SDL_GL_SwapWindow(m_Window);
	}

	void Window::Update()
	{
		//Swap the window
		SDL_GL_SwapWindow(m_Window);
	}

	void Window::Close()
	{
		//Set is closed to true
		m_isClosed = true;
	}

	void Window::Warp(Vector2f WarpPos)
	{
		//Set the mouse position to the position passed in
		SDL_WarpMouseInWindow(m_Window, WarpPos.GetX(), WarpPos.GetY());
	}
}