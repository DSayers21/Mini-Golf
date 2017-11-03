#include "Cuboid.h"

namespace D3DEngine
{
	Cuboid::Cuboid()
	{
		m_Position = vec3(0,0,0);
		InitCuboid(1, 1, 1);
	}

	Cuboid::Cuboid(float Width, float Height, float Length, vec3 Position)
	{
		m_Position = Position;
		InitCuboid(Width, Height, Length);
	}

	Cuboid::~Cuboid()
	{

	}

	void Cuboid::InitCuboid(float Width, float Height, float Length)
	{
		//First Vect is topLeft
		//Second Vect is bottomLeft
		//Third Vect is bottomRight
		//Fourth Vect is Top Right

		//Get Half Points
		float HalfWidth = Width / 2;
		float HalfHeight = Height / 2;
		float HalfLength = Length / 2;

		//Init Points
		vec3 FTopLeft = vec3(-HalfWidth, HalfHeight, HalfLength);
		vec3 FBottomLeft = vec3(-HalfWidth, -HalfHeight, HalfLength);
		vec3 FBottomRight = vec3(HalfWidth, -HalfHeight, HalfLength);
		vec3 FTopRight = vec3(HalfWidth, HalfHeight, HalfLength);
		vec3 BTopLeft = vec3(HalfWidth, HalfHeight, -HalfLength);
		vec3 BBottomLeft = vec3(HalfWidth, -HalfHeight, -HalfLength);
		vec3 BBottomRight = vec3(-HalfWidth, -HalfHeight, -HalfLength);
		vec3 BTopRight = vec3(-HalfWidth, HalfHeight, -HalfLength);
		//End Init Points

		//Create Sides
		vec3 SideA[4]{ FTopLeft, FBottomLeft, FBottomRight, FTopRight }; //Front
		vec3 SideB[4]{ BTopLeft, BBottomLeft, BBottomRight, BTopRight }; //Back
		vec3 SideC[4]{ BTopRight, BBottomRight, FBottomLeft, FTopLeft }; //Left
		vec3 SideD[4]{ FTopRight, FBottomRight , BBottomLeft, BTopLeft };//Right
		vec3 SideE[4]{ BTopRight, FTopLeft, FTopRight, BTopLeft };//Top
		vec3 SideF[5]{ FBottomLeft, BBottomRight, BBottomLeft, FBottomRight };//Bottom
		//End Create Sides

		//Update Rects Array
		m_Rects[0] = new Rect(SideA, m_Position, Colour(1, 0, 0));
		m_Rects[1] = new Rect(SideB, m_Position, Colour(0, 1, 0));
		m_Rects[2] = new Rect(SideC, m_Position, Colour(0, 0, 1));
		m_Rects[3] = new Rect(SideD, m_Position, Colour(0, 0, 1));
		m_Rects[4] = new Rect(SideE, m_Position, Colour(0.5, 0, 1));
		m_Rects[5] = new Rect(SideF, m_Position, Colour(0, 0, 1));
		//End Update Rects Array
	}

	void Cuboid::Draw()
	{
		glTranslatef(m_Position(0), m_Position(1), m_Position(2));
		glPushMatrix();
		//Draw
		for (int i = 0; i < 6; i++)
		{
			glBegin(GL_POLYGON);
			m_Rects[i]->Draw(true);
			Shape::Draw();
			glEnd();
		}
		glPopMatrix();
	}
}