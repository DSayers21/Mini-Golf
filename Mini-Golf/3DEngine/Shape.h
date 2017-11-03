#pragma once


#include <glut.h>
#include "Vecmath.h"


namespace D3DEngine
{
	struct Colour
	{
		Colour()
		{

		}

		Colour(float R, float G, float B)
		{
			SetColour(R, G, B);
		}

		void SetColour(float sR, float sG, float sB)
		{
			R = sR;
			G = sG;
			B = sB;
		}

		//Members
		float R;
		float G;
		float B;
	};

	class Shape
	{
	public:
		Shape();
		~Shape();

		void Draw();

		//Setters
		void SetColour(float R, float G, float B) { m_Col.SetColour(R, G, B); }
		void SetColour(Colour Col) { m_Col = Col; }
		void SetPosition(vec3 Position) { m_Position = Position; }

	protected:
		Colour m_Col; //RGB
		vec3 m_Position;

		int m_NumOfVertices;
		vec3* m_Vertices;
	};
}