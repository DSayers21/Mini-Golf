//Includes
#include "TextRendering.h"

namespace D3DEngine
{
	TextRendering::TextRendering(Window* Window) :
		m_Window(Window)
	{
		//Empty
	}

	TextRendering::~TextRendering()
	{
		//Emptys
	}

	void TextRendering::Render(const std::string& message, Vector3f color, int x, int y)
	{
		//Set the view mode to 2D plane
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, m_Window->GetWidth(), 0, m_Window->GetHeight());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		//Disable Textures
		glDisable(GL_TEXTURE);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);

		int Len;
		//Set the colour
		glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0);
		//Set the positions
		glRasterPos2i(x, y);
		
		//Loop over the string and print each character
		for (int i = 0, len = strlen(message.c_str()); i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)message[i]);

		//Enable Textures
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE);
		glEnable(GL_CULL_FACE);
		//Switch back to 3D projection
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
}