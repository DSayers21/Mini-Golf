#include "Triangle.h"

namespace D3DEngine
{
	Triangle::Triangle()
	{
		m_Position = vec3(0, 0, 0);
		
		InitTriangle(vec3(-0.5, -0.5, 0.5), vec3(-0.5, 0.5, -0.5), vec3(0.5, -0.5, 0.5), Colour(0, 1, 0));
	}

	Triangle::Triangle(vec3 Vert[3], vec3 Postion, Colour Col)
	{
		m_Position = Postion;

		InitTriangle(Vert[0], Vert[1], Vert[2], Col);
	}

	Triangle::~Triangle()
	{
		delete[] m_Vertices;
	}

	void Triangle::InitTriangle(vec3 A, vec3 B, vec3 C, Colour Col)
	{
		m_NumOfVertices = 3;
		m_Vertices = new vec3[m_NumOfVertices];

		m_Vertices[0] = A;
		m_Vertices[1] = B;
		m_Vertices[2] = C;

		SetColour(Col);
	}
	void Triangle::Draw()
	{
		glTranslatef(m_Position(0), m_Position(1), m_Position(2));
		glPushMatrix();

		glBegin(GL_TRIANGLES);
		Shape::Draw();
		glEnd();

		glPopMatrix();
	}
}