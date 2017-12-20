#include "TextRendering.h"

namespace D3DEngine
{
	TextRendering::TextRendering(Window* Window)
	{
		m_Window = Window;
	}


	TextRendering::~TextRendering()
	{
	}

	void TextRendering::Render(std::string message, Vector3f color, int x, int y)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, m_Window->GetWidth(), 0, m_Window->GetHeight());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		int Len;
		glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0);
		glRasterPos2i(x, y);

		glDisable(GL_TEXTURE);
		glDisable(GL_TEXTURE_2D);

		for (int i = 0, len = strlen(message.c_str()); i < len; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)message[i]);
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE);

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
}