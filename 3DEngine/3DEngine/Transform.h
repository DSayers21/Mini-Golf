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
		Vector3f GetTranslation() { return m_Translation; }
		Vector3f GetRotation() { return m_Rotation; }
		Vector3f GetScaling() { return m_Scaling; }
		Matrix4f GetProjectedTransformation();
		Camera* GetCamera() const { return m_Camera; }
		//Setters
		void SetProjection(float FOV, float Width, float Height, float zNear, float zFar);
		void SetTranslation(Vector3f Translation) { m_Translation = Translation; }
		void SetTranslation(float x, float y, float z) { m_Translation = Vector3f(x,y,z); }
		void SetRotation(Vector3f Rotation) { m_Rotation = Rotation; }
		void SetRotation(float x, float y, float z) { m_Rotation = Vector3f(x, y, z); }
		void SetScaling(Vector3f Scaling) { m_Scaling = Scaling; }
		void SetScaling(float x, float y, float z) { m_Scaling = Vector3f(x, y, z); }
		void SetCamera(Camera* camera) { m_Camera = camera; }

	private:
		//Represents x,y,z of translation
		Vector3f m_Translation = Vector3f(0,0,0);
		Vector3f m_Rotation = Vector3f(0, 0, 0);
		Vector3f m_Scaling = Vector3f(1, 1, 1);
		//
		float m_zNear;
		float m_zFar;
		float m_Width;
		float m_Height;
		float m_FOV;

		Camera* m_Camera;
	};
}