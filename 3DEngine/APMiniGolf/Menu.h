#pragma once

//Includes
#include <map>
#include "Window.h"
#include "Vector3f.h"

//Forward declarations
namespace D3DEngine
{
	class RenderEngine;
	class GetInput;
}

class Button
{
public:
	//Empty Constructor
	Button() {}
	//Constructor
	Button(std::string Text, int x, int y, int h, int w,
		D3DEngine::Vector3f Colour, D3DEngine::Vector3f OverColour, bool Active);
	//Empty Destructor
	~Button() {}
	//Do input for the button
	bool Input(D3DEngine::GetInput * Inpt, int ScreenHeight);
	//Render the button
	void Render(D3DEngine::RenderEngine* Render);

	//Getters
	inline std::string GetText() { return m_Text; }
	//Setters
	inline void SetActive(bool Active) { m_Active = Active; }

private:
	//Button text
	std::string m_Text;
	//Button Position, and width and height
	int X, Y, H, W;
	//If the button is being hovered over
	bool m_Over = false;
	//If the button has been clicked
	bool m_Active = false;
	//Normal Colour of the button
	D3DEngine::Vector3f m_Colour;
	//Hover over Colour of the button
	D3DEngine::Vector3f m_OverColour;
};

class ButtonGroup
{
public:
	//Empty Contructor
	ButtonGroup() {}
	//Empty Destructor
	~ButtonGroup() {}
	//Set all buttons in the group to active
	void SetAllToNotActive();
	//Do input for all buttons
	std::string InputButtons(D3DEngine::GetInput * Inpt, int ScreenHeight);
	//Render all buttons
	void RenderButtons(D3DEngine::RenderEngine* Render);
	//Add button to map
	void AddButton(Button& button);

private:
	//Map of the buttons, keyed by the text on the button
	std::map<std::string, Button> m_Buttons = std::map<std::string, Button>();
};