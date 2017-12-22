#pragma once

#include <map>
#include "Window.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class RenderEngine;
	class GetInput;
}

class Button
{
public:
	Button() {}
	Button(std::string Text, int x, int y, int h, int w,
		D3DEngine::Vector3f Colour, D3DEngine::Vector3f OverColour, bool Active);
	~Button() {}

	bool Input(D3DEngine::GetInput * Inpt, int ScreenHeight);

	void Render(D3DEngine::RenderEngine* Render);

	inline std::string GetText() { return m_Text; }
	inline void SetActive(bool Active) { m_Active = Active; }

private:
	std::string m_Text;
	int X, Y, H, W;
	bool m_Over = false;
	bool m_Active = false;
	D3DEngine::Vector3f m_Colour;
	D3DEngine::Vector3f m_OverColour;
};

class ButtonGroup
{
public:
	ButtonGroup() {}
	~ButtonGroup() {}

	void SetAllToNotActive();

	std::string InputButtons(D3DEngine::GetInput * Inpt, int ScreenHeight);

	void RenderButtons(D3DEngine::RenderEngine* Render);

	void AddButton(Button& button);

private:
	std::map<std::string, Button> m_Buttons = std::map<std::string, Button>();
};