#pragma once
#include "Vector3f.h"

namespace D3DEngine
{
	class Vert
	{
	public:
		Vert() { m_Pos = Vector3f(0, 0, 0); };
		Vert(Vector3f Pos) : m_Pos(Pos){}
		~Vert();

		const static int SIZE = 3;

	private:
		Vector3f m_Pos = Vector3f(0, 0, 0);;
	};
}