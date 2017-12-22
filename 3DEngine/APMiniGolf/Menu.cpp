#include "Menu.h"

#include "RenderEngine.h"
#include "Window.h"

Button::Button(std::string Text, int x, int y, int h, int w,
	D3DEngine::Vector3f Colour, D3DEngine::Vector3f OverColour, bool Active) :
	m_Text(Text), X(x), Y(y), H(h), W(w), m_Colour(Colour), m_OverColour(OverColour), m_Active(Active)
{
	//Empty
}

bool Button::Input(D3DEngine::GetInput* Inpt, int ScreenHeight)
{
	D3DEngine::Vector2f MousePos = Inpt->GetMousePos();
	int ActualY = ScreenHeight - Y;
	if (((MousePos.GetX() < (X + (W * 2))) && (MousePos.GetX() > (X)))
		&& ((MousePos.GetY() < ActualY) && (MousePos.GetY() > ActualY - H)))
	{
		m_Over = true;
		//Check Left Mouse
		if (Inpt->GetMouseDown(D3DEngine::MOUSE_LEFT_BUTTON))
			return true;
	}
	else
		m_Over = false;
	return false;
}

void Button::Render(D3DEngine::RenderEngine* Render)
{
	if (m_Active)
	{
		Render->AddText(m_Text, D3DEngine::TextToRender(m_Text, m_OverColour, X, Y));
	}
	else
	{
		if (m_Over)
			Render->AddText(m_Text, D3DEngine::TextToRender(m_Text, m_OverColour, X, Y));
		else
			Render->AddText(m_Text, D3DEngine::TextToRender(m_Text, m_Colour, X, Y));
	}
}

void ButtonGroup::SetAllToNotActive()
{
	for (std::map<std::string, Button>::iterator it = m_Buttons.begin(); it != m_Buttons.end();)
	{
		it->second.SetActive(false);
		it++;
	}
}

std::string ButtonGroup::InputButtons(D3DEngine::GetInput* Inpt, int ScreenHeight)
{
	for (std::map<std::string, Button>::iterator it = m_Buttons.begin(); it != m_Buttons.end();)
	{
		if (it->second.Input(Inpt, ScreenHeight))
		{
			SetAllToNotActive();
			it->second.SetActive(true);
			return it->first;
		}
		it++;
	}
	//No Buttons Clicked
	return "NULL";
}

void ButtonGroup::RenderButtons(D3DEngine::RenderEngine * Render)
{
	for (std::map<std::string, Button>::iterator it = m_Buttons.begin(); it != m_Buttons.end();)
	{
		it->second.Render(Render);
		it++;
	}
}

//Button Group
void ButtonGroup::AddButton(Button & button)
{
	m_Buttons.insert(std::pair<std::string, Button>(button.GetText(), button));
}