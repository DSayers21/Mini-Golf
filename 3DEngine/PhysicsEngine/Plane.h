#pragma once

#include "Vector3f.h"
#include "IntersectData.h"
#include "BoundingSphere.h"
#include "Collider.h"

namespace D3DEngine
{
	class Plane : public Collider
	{
	public:
		Plane(const Vector3f& Normal, float Distance);
		~Plane();

		Plane Normalise() const;
		IntersectData IntersectPlane(const Plane & other) const;
		IntersectData IntersectSphere(const BoundingSphere& other) const;
		virtual void Transform(const Vector3f Translation);

		//Getters
		inline const Vector3f& GetNormal() const { return m_Normal; }
		inline float GetDistance() const { return m_Distance; }

	private:
		const Vector3f m_Normal;
		const float m_Distance;
	};
}