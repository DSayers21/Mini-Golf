#include "Menu.h"

#include "RenderEngine.h"
#include "Window.h"

Rectangle::Rectangle(std::string Text, int x, int y, int h, int w,
	D3DEngine::Vector3f Colour, D3DEngine::Vector3f OverColour, bool Active) :
	m_Text(Text), X(x), Y(y), H(h), W(w), m_Colour(Colour), m_OverColour(OverColour), m_Active(Active)
{
}


bool Rectangle::Input(D3DEngine::GetInput* Inpt, int ScreenHeight)
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

void Rectangle::Render(D3DEngine::RenderEngine* Render)
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