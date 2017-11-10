#pragma once
#include "Vector3f.h"
#include "Vector2f.h"
namespace D3DEngine
{
	class Vert
	{
	public:
		Vert() { *this = Vert(Vector3f(0, 0, 0), Vector2f(0, 0), Vector3f(0, 0, 0)); };
		Vert(Vector3f& Pos) { *this = Vert(Pos, Vector2f(0, 0), Vector3f(0, 0, 0)); }
		Vert(Vector3f& Pos, Vector2f& TexCoord) { *this = Vert(Pos, TexCoord, Vector3f(0, 0, 0)); }
		Vert(Vector3f& Pos, Vector2f& TexCoord, Vector3f& Normal) : m_Pos(Pos), m_TexCoord(TexCoord), m_Normal(Normal){}
		~Vert();

		//Getters
		inline Vector3f& GetPos() { return m_Pos; }
		inline Vector2f& GetTexCoord() { return m_TexCoord; }
		inline Vector3f& GetNormal() { return m_Normal; }
		//Setters
		inline void SetPos(Vector3f Pos) { m_Pos = Pos; }
		inline void SetTexCoord(Vector2f TexCoord) { m_TexCoord = TexCoord; }
		inline void SetNormal(Vector3f Normal) { m_Normal = Normal; }


	private:
		Vector3f m_Pos = Vector3f(0, 0, 0);
		Vector2f m_TexCoord = Vector2f(0, 0);
		Vector3f m_Normal = Vector3f(0, 0, 0);
	};
}