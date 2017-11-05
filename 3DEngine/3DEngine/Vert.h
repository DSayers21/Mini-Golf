#pragma once
#include "Vector3f.h"

namespace D3DEngine
{
	class Vert
	{
	public:
		Vert(Vector3f Pos) : m_Pos(Pos){}
		~Vert();

		const static int SIZE = 3;

	private:
		Vector3f m_Pos;
	};
}