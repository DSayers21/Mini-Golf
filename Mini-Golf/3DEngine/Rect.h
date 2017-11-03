#pragma once
#include "Shape.h"

namespace D3DEngine
{
	class Rect : public Shape
	{
	public:
		Rect();
		Rect(vec3 Vert[4], vec3 Postion, Colour Col);
		Rect(float Width, float Height, float Length, vec3 Position, Colour Col);
		
		~Rect();

		void InitRect(vec3 A, vec3 B, vec3 C, vec3 D, Colour Col);
		void Draw(bool Single = false);
	};
}