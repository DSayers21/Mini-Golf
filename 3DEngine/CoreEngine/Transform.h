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
		Transform::Transform(const Transform &other);

		Transform& operator=(const Transform &other);

		Matrix4f GetTransformation();

		//Getters
		inline Vector3f* GetPosition() { return &m_Position; }
		inline Quaternion* GetRotation() { return &m_Rotation; }
		inline Vector3f* GetScaling() { return &m_Scaling; }
		//Setters
		void SetPosition(Vector3f Position) { m_Position = Position; }
		//inline inline void SetPosition(float x, float y, float z) { m_Position = Vector3f(x,y,z); }
		inline void SetRotation(Quaternion* Rotation) { m_Rotation = *Rotation; }
		inline void SetRotation(float x, float y, float z, float w) { m_Rotation = Quaternion(x,y,z,w); }
		inline void SetScaling(Vector3f Scaling) { m_Scaling = Scaling; }
		inline void SetScaling(float x, float y, float z) { m_Scaling = Vector3f(x,y,z); }
		inline void SetParent(Transform* Parent) { m_Parent = Parent; }
		//IfBoolean Funcs
		bool HasChanged();

		Vector3f GetTransformedPos();

		void Rotate(Vector3f Axis, float Angle);

		void Update();

		Quaternion GetTransformedRot();

	private:
		Matrix4f* GetParentMatrix();

		//Represents x,y,z of translation
		Vector3f m_Position = Vector3f(0,0,0);
		Quaternion m_Rotation = Quaternion(0,0,0,1);
		Vector3f m_Scaling = Vector3f(1,1,1);

		bool FirstTime = true;
		Vector3f m_PrevPosition;
		Quaternion m_PrevRotation;
		Vector3f m_PrevScaling;

		Transform* m_Parent;
		Matrix4f m_ParentMatrix;
	};

}