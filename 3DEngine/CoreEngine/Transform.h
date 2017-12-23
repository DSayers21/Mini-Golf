#pragma once

//Includes
#include "Quaternion.h"
#include "Vector3f.h"
#include "Matrix4f.h"
#include <iostream>

namespace D3DEngine
{
	class Transform
	{
	public:
		//Constructor
		Transform();
		//Destructor
		~Transform();
		//Copy Constructor
		Transform::Transform(const Transform &other);
		//Equals Operator
		Transform& operator=(const Transform &other);

		//Get the transformation
		Matrix4f GetTransformation();

		//Getters
		inline Vector3f* GetPosition()   { return &m_Position; }
		inline Quaternion* GetRotation() { return &m_Rotation; }
		inline Vector3f* GetScaling()    { return &m_Scaling;  }

		//Setters
		inline void SetPosition(Vector3f Position) { m_Position = Position; }
		inline void SetRotation(Quaternion* Rotation) { m_Rotation = *Rotation; }
		inline void SetRotation(float x, float y, float z, float w) { m_Rotation = Quaternion(x,y,z,w); }
		inline void SetScaling(Vector3f Scaling) { m_Scaling = Scaling; }
		inline void SetScaling(float x, float y, float z) { m_Scaling = Vector3f(x,y,z); }
		inline void SetParent(Transform* Parent) { m_Parent = Parent; }
		
		//If the transformation has changed
		bool HasChanged();

		//Get the transformed position
		Vector3f GetTransformedPos();
		//Get the transformed rotation
		Quaternion GetTransformedRot();
		//Rotate
		void Rotate(Vector3f Axis, float Angle);

		//Update the transform
		void Update();

	private:
		//Get Parent Matrix
		Matrix4f* GetParentMatrix();

		//Represents x,y,z of translation
		Vector3f m_Position = Vector3f(0,0,0);
		Quaternion m_Rotation = Quaternion(0,0,0,1);
		Vector3f m_Scaling = Vector3f(1,1,1);

		//If its just been created
		bool m_FirstTime = true;

		//Represents x,y,z of previous translation
		Vector3f m_PrevPosition;
		Quaternion m_PrevRotation;
		Vector3f m_PrevScaling;

		//Parent Transform
		Transform* m_Parent;
		//Parent Matrix
		Matrix4f m_ParentMatrix;
	};
}