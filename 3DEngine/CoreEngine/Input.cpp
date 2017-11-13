#include "Input.h"

namespace D3DEngine
{
	GetInput::GetInput()
	{
		m_WarpMousePos = new Vector2f(0,0);
	}

	GetInput::~GetInput()
	{
	}

	SDL_Event GetInput::PollEvent()
	{
		//Poll Events
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				m_isClosed = true;

			if (e.type == SDL_MOUSEMOTION)
			{
				m_MouseX = e.motion.x;
				m_MouseY = e.motion.y;
			}

			if (e.type == SDL_KEYDOWN)
			{
				int value = e.key.keysym.scancode;

				//Ensure Input hasnt already been captured
				if (!m_Inputs[value])
				{
					m_Inputs[value] = true;
					m_DownKeys[value] = true;
				}
			}
			if (e.type == SDL_KEYUP)
			{
				int value = e.key.keysym.scancode;

				m_Inputs[value] = false;
				m_UpKeys[value] = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int value = e.button.button;

				//Ensure Input hasnt already been captured
				if (!m_MouseInput[value])
				{
					m_MouseInput[value] = true;
					m_DownMouse[value] = true;
				}
			}
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				int value = e.button.button;

				m_MouseInput[value] = false;
				m_UpMouse[value] = true;
			}
		}
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
		PollEvent();
	}
	void GetInput::SetCursor(bool Visible)
	{
		(Visible) ? SDL_ShowCursor(1) : SDL_ShowCursor(0);
	}

	void GetInput::SetMousePosition(Vector2f Pos)
	{
		m_warpMouse = true;
		m_WarpMousePos->SetX(Pos.GetX());
		m_WarpMousePos->SetY(Pos.GetY());
	}
}