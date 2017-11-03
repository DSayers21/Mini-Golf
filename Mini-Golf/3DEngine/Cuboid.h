#pragma once
#include "Shape.h"
#include "Rect.h"

namespace D3DEngine
{
	class Cuboid : public Shape
	{
	public:
		Cuboid();
		Cuboid(float Width, float Height, float Length, vec3 Position);
		~Cuboid();

		void InitCuboid(float Width, float Height, float Length);
		void Draw();

	private:
		Rect* m_Rects[6];

		Rect* m_SideA;
		Rect* m_SideB;
	};
}