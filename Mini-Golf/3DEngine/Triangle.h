#pragma once
#include "Shape.h"

namespace D3DEngine
{
	class Triangle : public Shape
	{
	public:
		Triangle();
		Triangle(vec3 Vert[3], vec3 Postion, Colour Col);
		~Triangle();

		void InitTriangle(vec3 A, vec3 B, vec3 C, Colour Col);

		void Draw();
	};
}