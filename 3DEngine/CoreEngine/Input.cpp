//Inputs
#include "Input.h"

namespace D3DEngine
{
	GetInput::GetInput(Window* Window)
	{
		//Set the window
		m_Window = Window;
		//Set mouse warped pos to default
		m_WarpMousePos = Vector2f(0,0);
	}

	GetInput::~GetInput()
	{
		//Empty
	}

	SDL_Event GetInput::PollEvent()
	{
		//Poll Events
		while (SDL_PollEvent(&e))
		{
			//If X button has been pressed
			if (e.type == SDL_QUIT)
				m_isClosed = true;	//Set window to closed
			//Check if mouse is moving
			if (e.type == SDL_MOUSEMOTION)
			{
				//Update mouse position
				m_MouseX = e.motion.x;
				m_MouseY = e.motion.y;
			}
			//Check if a key is down
			if (e.type == SDL_KEYDOWN)
			{
				//Get the key code
				int value = e.key.keysym.scancode;

				//Ensure Input hasnt already been captured
				if (!m_Inputs[value])
				{
					//Update inputs
					m_Inputs[value] = true;
					m_DownKeys[value] = true;
				}
			}
			if (e.type == SDL_KEYUP)
			{
				//Get the key code
				int value = e.key.keysym.scancode;
				//Update inputs
				m_Inputs[value] = false;
				m_UpKeys[value] = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//Get the mouse key code
				int value = e.button.button;

				//Ensure Input hasnt already been captured
				if (!m_MouseInput[value])
				{
					//Update inputs
					m_MouseInput[value] = true;
					m_DownMouse[value] = true;
				}
			}
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				//Get the mouse key code
				int value = e.button.button;
				//Update inputs
				m_MouseInput[value] = false;
				m_UpMouse[value] = true;
			}
		}
		//Return the SDL event
		return SDL_Event();
	}

	void GetInput::Update()
	{
		//Reset Keyboard Buttons
		for (int i = 0; i < NUM_KEYS; i++)
		{
			m_DownKeys[i] = false;
			m_UpKeys[i] = false;
		}
		//Reset Mouse Buttons
		for (int i = 0; i < NUM_MOUSEBUTTONS; i++)
		{
			m_DownMouse[i] = false;
			m_UpMouse[i] = false;
		}
		//Poll the keyboard and mouse for events
		PollEvent();
	}
	void GetInput::SetCursor(bool Visible)
	{
		//Set the cursor to visible or not
		(Visible) ? SDL_ShowCursor(1) : SDL_ShowCursor(0);
	}

	void GetInput::SetMousePosition(Vector2f Pos)
	{
		//Set warp mouse to true
		m_warpMouse = true;
		//Set the position of the warped mouse
		m_WarpMousePos.SetX(Pos.GetX());
		m_WarpMousePos.SetY(Pos.GetY());
	}
}