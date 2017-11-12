#pragma once

#include "Vector3f.h"
#include "Matrix4f.h"
#include "Camera.h"

namespace D3DEngine
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		Matrix4f GetTransformation();

		//Getters
		Vector3f GetPosition() { return m_Position; }
		Vector3f GetRotation() { return m_Rotation; }
		Vector3f GetScaling() { return m_Scaling; }
		//Setters
		void SetPosition(Vector3f Position) { m_Position = Position; }
		void SetPosition(float x, float y, float z) { m_Position = Vector3f(x,y,z); }
		void SetRotation(Vector3f Rotation) { m_Rotation = Rotation; }
		void SetRotation(float x, float y, float z) { m_Rotation = Vector3f(x,y,z); }
		void SetScaling(Vector3f Scaling) { m_Scaling = Scaling; }
		void SetScaling(float x, float y, float z) { m_Scaling = Vector3f(x,y,z); }

	private:
		//Represents x,y,z of translation
		Vector3f m_Position = Vector3f(7,0,7);
		Vector3f m_Rotation = Vector3f(0,0,0);
		Vector3f m_Scaling = Vector3f(1,1,1);
	};
}