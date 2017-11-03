#include "Shape.h"

#include <stdio.h>

namespace D3DEngine
{
	Shape::Shape()
	{
		//Empty
	}


	Shape::~Shape()
	{
		//Empty
	}

	void Shape::Draw()
	{
		glColor3f(m_Col.R, m_Col.G, m_Col.B);
		for (int i = 0; i < m_NumOfVertices; i++)
		{
			glVertex3f(m_Vertices[i](0), m_Vertices[i](1), m_Vertices[i](2));
		}
	}
}