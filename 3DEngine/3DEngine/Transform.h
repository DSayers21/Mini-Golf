#pragma once

#include "Vector3f.h"
#include "Matrix4f.h"

namespace D3DEngine
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		Matrix4f GetTransformation();

		Vector3f GetTranslation() { return m_Translation; }
		void SetTranslation(Vector3f Translation) { m_Translation = Translation; }
		void SetTranslation(float x, float y, float z) { m_Translation = Vector3f(x,y,z); }
	private:
		//Represents x,y,z of translation
		Vector3f m_Translation = Vector3f(0,0,0);
	};
}