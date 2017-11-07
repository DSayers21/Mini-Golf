#pragma once
#include "Vector2f.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class Vert
	{
	public:
		Vert() { m_Pos = Vector3f(0, 0, 0); m_TexCoord = Vector2f(0, 0); };
		Vert(Vector3f Pos) : m_Pos(Pos), m_TexCoord(0,0){}
		Vert(Vector3f Pos, Vector2f TexCoord) : m_Pos(Pos), m_TexCoord(TexCoord) {}
		~Vert();

		//Getters
		inline Vector3f GetPos() { return m_Pos; }
		inline Vector2f GetTexCoord() { return m_TexCoord; }
		//Setters
		inline void SetPos(Vector3f Pos) { m_Pos = Pos; }
		inline void SetTexCoord(Vector2f TexCoord) { m_TexCoord = TexCoord; }
		
		const static int SIZE = 5;

	private:
		Vector3f m_Pos = Vector3f(0, 0, 0);
		Vector2f m_TexCoord = Vector2f(0, 0);
	};
}