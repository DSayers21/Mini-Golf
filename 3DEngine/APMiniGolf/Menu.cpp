//Includes
#include "Menu.h"
#include "RenderEngine.h"
#include "Input.h"

Button::Button(std::string Text, int x, int y, int h, int w,
	D3DEngine::Vector3f Colour, D3DEngine::Vector3f OverColour, bool Active) :
	m_Text(Text), X(x), Y(y), H(h), W(w), m_Colour(Colour), m_OverColour(OverColour), m_Active(Active)
{
	//Empty
}

bool Button::Input(D3DEngine::GetInput* Inpt, int ScreenHeight)
{
	//Get mouse position
	D3DEngine::Vector2f MousePos = Inpt->GetMousePos();
	//Get the actual Y position of the button
	int ActualY = ScreenHeight - Y;
	//Check if the mouse is within the area of the button
	if (((MousePos.GetX() < (X + (W * 2))) && (MousePos.GetX() > (X)))
		&& ((MousePos.GetY() < ActualY) && (MousePos.GetY() > ActualY - H)))
	{
		m_Over = true;	//Set over to true
		//Check Left Mouse, return true if the button is pressed
		if (Inpt->GetMouseDown(D3DEngine::MOUSE_LEFT_BUTTON))
			return true;
	}
	else
		m_Over = false;	//Set over to false
	return false;	//Return false (button not pressed)
}

void Button::Render(D3DEngine::RenderEngine* Render)
{
	//If the button is active, render over colour
	if (m_Active)
		Render->AddText(m_Text, D3DEngine::TextToRender(m_Text, m_OverColour, X, Y));
	else //Else check if the button is being hovered over
	{
		if (m_Over)	//If hovered over, render over colour
			Render->AddText(m_Text, D3DEngine::TextToRender(m_Text, m_OverColour, X, Y));
		else 	//If not hovered over, render normal colour
			Render->AddText(m_Text, D3DEngine::TextToRender(m_Text, m_Colour, X, Y));
	}
}

void ButtonGroup::SetAllToNotActive()
{
	//Go through all buttons and set them to not active
	for (std::map<std::string, Button>::iterator it = m_Buttons.begin(); it != m_Buttons.end();)
	{
		it->second.SetActive(false);
		it++;	//Increment
	}
}

std::string ButtonGroup::InputButtons(D3DEngine::GetInput* Inpt, int ScreenHeight)
{
	//Loop over all buttons
	for (std::map<std::string, Button>::iterator it = m_Buttons.begin(); it != m_Buttons.end();)
	{
		//Check if the current button is being clicked
		if (it->second.Input(Inpt, ScreenHeight))
		{
			//Set all the not active
			SetAllToNotActive();
			//Set current button to active
			it->second.SetActive(true);
			//Return the name of the button which was clicked
			return it->first;
		}
		//Increment
		it++;
	}
	//No Buttons Clicked, return NULL
	return "NULL";
}

void ButtonGroup::RenderButtons(D3DEngine::RenderEngine * Render)
{
	//Loop over all the buttons and render them
	for (std::map<std::string, Button>::iterator it = m_Buttons.begin(); it != m_Buttons.end();)
	{
		it->second.Render(Render);
		it++;	//Increment
	}
}

void ButtonGroup::AddButton(Button & button)
{
	//Add button to the map
	m_Buttons.insert(std::pair<std::string, Button>(button.GetText(), button));
}