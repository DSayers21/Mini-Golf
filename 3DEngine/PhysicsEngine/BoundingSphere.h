#pragma once

#include "Vector3f.h"
#include "IntersectData.h"
#include "Collider.h"

namespace D3DEngine
{
	class BoundingSphere : public Collider
	{
	public:
		BoundingSphere(Vector3f Center, float Radius);
		~BoundingSphere();

		IntersectData IntersectBoundingSphere(const BoundingSphere& other);

		virtual void Transform(const Vector3f Translation);
		

		//Getters
		virtual Vector3f GetCenter() const { return m_Center; }
		inline float GetRadius() const { return m_Radius; }
	private:
		Vector3f m_Center;
		float m_Radius;
	};
}