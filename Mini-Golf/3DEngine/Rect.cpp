#include "Rect.h"

namespace D3DEngine
{
	Rect::Rect()
	{
		m_Position = vec3(0, 0, 0);

		InitRect(vec3(-0.5, 0.5, 0.5), vec3(-0.5, -0.5, 0.5), vec3(0.5, -0.5, 0.5), vec3(0.5, 0.5, 0.5), Colour(1, 0.64705882352, 0));
	}

	Rect::Rect(vec3 Vert[4], vec3 Postion, Colour Col)
	{
		m_Position = Postion;

		InitRect(Vert[0], Vert[1], Vert[2], Vert[3], Col);
	}

	Rect::Rect(float Width, float Height, float Length, vec3 Position, Colour Col)
	{
		m_Position = Position;

		//Get Half Points
		float HalfWidth = Width / 2;
		float HalfHeight = Height / 2;
		float HalfLength = Length / 2;

		//Init Points
		vec3 FTopLeft = vec3(-HalfWidth, HalfHeight, HalfLength);
		vec3 FBottomLeft = vec3(-HalfWidth, -HalfHeight, HalfLength);
		vec3 FBottomRight = vec3(HalfWidth, -HalfHeight, HalfLength);
		vec3 FTopRight = vec3(HalfWidth, HalfHeight, HalfLength);
		//End Init Points

		InitRect(FTopLeft, FBottomLeft, FBottomRight, FTopRight, Col);
	}

	Rect::~Rect()
	{
		delete[] m_Vertices;
	}

	void Rect::InitRect(vec3 A, vec3 B, vec3 C, vec3 D, Colour Col)
	{
		m_NumOfVertices = 4;
		m_Vertices = new vec3[m_NumOfVertices];

		m_Vertices[0] = A;
		m_Vertices[1] = B;
		m_Vertices[2] = C;
		m_Vertices[3] = D;

		SetColour(Col);
	}

	void Rect::Draw(bool Single)
	{
		glTranslatef(m_Position(0), m_Position(1), m_Position(2));
		glPushMatrix();

		glBegin(GL_POLYGON);
		Shape::Draw();
		glEnd();

		glPopMatrix();
	}
}